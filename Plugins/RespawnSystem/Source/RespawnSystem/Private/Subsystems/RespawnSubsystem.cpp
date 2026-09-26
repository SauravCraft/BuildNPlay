#include "Subsystems/RespawnSubsystem.h"
#include "Subsystems/SaveManagerSubsystem.h"
#include "SaveGames/SaveGameData.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

void URespawnSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (USaveManagerSubsystem* Save =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
        OnGameSavedHandle = Save->OnGameSaved.AddUObject(
            this,
            &URespawnSubsystem::HandleSave);

        OnGameLoadedHandle = Save->OnGameLoaded.AddUObject(
            this,
            &URespawnSubsystem::HandleLoad);

        UE_LOG(LogTemp, Warning,
            TEXT("Respawn Bound To Save Delegates"));
    }
    else
    {
        UE_LOG(LogTemp, Error,
            TEXT("Save Subsystem NOT FOUND"));
    }
}


void URespawnSubsystem::Deinitialize()
{
    if (USaveManagerSubsystem* Save =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
        if (OnGameSavedHandle.IsValid())
        {
            Save->OnGameSaved.Remove(OnGameSavedHandle);
            OnGameSavedHandle.Reset();
        }

        if (OnGameLoadedHandle.IsValid())
        {
            Save->OnGameLoaded.Remove(OnGameLoadedHandle);
            OnGameLoadedHandle.Reset();
        }
    }

    Super::Deinitialize();
}


void URespawnSubsystem::SetCheckpoint(
    const FTransform& Checkpoint)
{
    if (!Checkpoint.IsValid())
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Invalid Checkpoint Transform"));

        return;
    }

    // Don't save/broadcast if nothing changed
    if (CurrentCheckpoint.Equals(Checkpoint))
    {
        return;
    }

    CurrentCheckpoint = Checkpoint;

    UE_LOG(LogTemp, Warning,
        TEXT("Checkpoint Updated: %s"),
        *CurrentCheckpoint.GetLocation().ToString());

    if (USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
        SaveSubsystem->SaveGame();
    }

    OnCheckpointActivated.Broadcast(CurrentCheckpoint);
}


bool URespawnSubsystem::IsCheckpointActivated(
    FName CheckpointId) const
{
    return CurrentActiveCheckpoints.Contains(
        CheckpointId);
}


void URespawnSubsystem::ActivateCheckpoint(
    FName CheckpointId)
{
    CurrentActiveCheckpoints.AddUnique(
        CheckpointId);
}


bool URespawnSubsystem::RespawnPlayer(APawn* Pawn, const FTransform& SpawnTransform)
{
    UE_LOG(LogTemp, Warning, TEXT("Respawn System Call"));


    if (!Pawn)
    {
        return false;
    }

    AController* Controller = Pawn->GetController();

    if (!Controller)
    {
        return false;
    }

    UWorld* World = GetWorld();

    if (!World)
    {
        return false;
    }

    FVector SpawnLocation = SpawnTransform.GetLocation();
    FRotator SpawnRotation = SpawnTransform.GetRotation().Rotator();

    Controller->UnPossess();

    if (Pawn)
    {
        Pawn->SetActorHiddenInGame(true);
        Pawn->SetActorEnableCollision(false);
        Pawn->DisableInput(nullptr);
        Pawn->SetLifeSpan(0.1f);
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    APawn* NewPawn = World->SpawnActor<APawn>(
        Pawn->GetClass(),
        SpawnLocation,
        SpawnRotation,
        SpawnParams);

    if (!NewPawn)
    {
        return false;
    }

    Controller->Possess(NewPawn);

    UE_LOG(LogTemp, Warning,
        TEXT("Pawn After Possess = %s"),
        *NewPawn->GetActorLocation().ToString());
    return true;
}


void URespawnSubsystem::HandleSave(USaveGameData* SaveGame)
{
    if (!SaveGame)
    {
        return;
    }

    // ============================================
    // SAVE CHECKPOINT
    // ============================================

    SaveGame->CurrentCheckpointTransform =
        CurrentCheckpoint;

    SaveGame->ActiveCheckpoints =
        CurrentActiveCheckpoints;


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Saved Checkpoint: %s"),
        *CurrentCheckpoint.GetLocation().ToString()
    );


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Active Checkpoints: %d"),
        CurrentActiveCheckpoints.Num()
    );
}


void URespawnSubsystem::HandleLoad(
    USaveGameData* SaveGame)
{
    if (!SaveGame)
    {
        return;
    }

    CurrentCheckpoint =
        SaveGame->CurrentCheckpointTransform;

    CurrentActiveCheckpoints =
        SaveGame->ActiveCheckpoints;


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Respawn Data Loaded")
    );


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Loaded Checkpoint: X=%.3f Y=%.3f Z=%.3f"),
        CurrentCheckpoint.GetLocation().X,
        CurrentCheckpoint.GetLocation().Y,
        CurrentCheckpoint.GetLocation().Z
    );


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Loaded Active Checkpoints: %d"),
        CurrentActiveCheckpoints.Num()
    );
}