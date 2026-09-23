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
        Save->OnGameSaved.AddUObject(
            this,
            &URespawnSubsystem::HandleSave);

        Save->OnGameLoaded.AddUObject(
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
        Save->OnGameSaved.RemoveUObject(
            this,
            &URespawnSubsystem::HandleSave);

        Save->OnGameLoaded.RemoveUObject(
            this,
            &URespawnSubsystem::HandleLoad);
    }

    UE_LOG(LogTemp, Log,
        TEXT("Respawn Subsystem Deinitialized"));

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


bool URespawnSubsystem::RespawnPlayer(
    APawn* Pawn,
    const FTransform& SpawnTransform)
{
    UE_LOG(LogTemp, Warning,
        TEXT("Respawn System Call"));

    if (!Pawn)
    {
        UE_LOG(LogTemp, Error,
            TEXT("Respawn failed: Pawn is null"));

        return false;
    }

    AController* Controller =
        Pawn->GetController();

    if (!Controller)
    {
        UE_LOG(LogTemp, Error,
            TEXT("Respawn failed: Controller is null"));

        return false;
    }

    UWorld* World = GetWorld();

    if (!World)
    {
        UE_LOG(LogTemp, Error,
            TEXT("Respawn failed: World is null"));

        return false;
    }


    // Save reference to old pawn
    APawn* OldPawn = Pawn;


    // Remove controller from old pawn
    Controller->UnPossess();


    // Spawn new pawn at checkpoint
    FActorSpawnParameters SpawnParams;

    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    APawn* NewPawn = World->SpawnActor<APawn>(
        OldPawn->GetClass(),
        SpawnTransform,
        SpawnParams);

    if (!NewPawn)
    {
        UE_LOG(LogTemp, Error,
            TEXT("Respawn failed: Could not spawn new pawn"));

        return false;
    }


    // Possess new pawn
    Controller->Possess(NewPawn);


    UE_LOG(LogTemp, Warning,
        TEXT("Pawn After Possess = %s"),
        *NewPawn->GetActorLocation().ToString());


    // Remove old pawn AFTER successful possession
    OldPawn->Destroy();


    return true;
}


void URespawnSubsystem::HandleSave(USaveGameData* SaveGame)
{
    if (!SaveGame)
    {
        return;
    }

    // ============================================
    // SAVE PLAYER TRANSFORM
    // ============================================

    if (UWorld* World = GetWorld())
    {
        if (APlayerController* PC =
            World->GetFirstPlayerController())
        {
            if (APawn* PlayerPawn = PC->GetPawn())
            {
                SaveGame->PlayerTransform =
                    PlayerPawn->GetActorTransform();

                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("RespawnSystem: Saved Player Transform: %s"),
                    *PlayerPawn->GetActorLocation().ToString()
                );
            }
            else
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("RespawnSystem: Player Pawn is NULL")
                );
            }
        }
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