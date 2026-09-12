#include "Subsystems/SaveManagerSubsystem.h"

#include "SaveGames/SaveGameData.h"

#include "Kismet/GameplayStatics.h"

void USaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

}

void USaveManagerSubsystem::Deinitialize()
{
    Super::Deinitialize();

    UE_LOG(LogTemp, Log, TEXT("SaveManager Deinitialized"));
}


bool USaveManagerSubsystem::SaveGame()
{
    if (!CurrentSaveGame)
    {
        CurrentSaveGame = Cast<USaveGameData>(
            UGameplayStatics::CreateSaveGameObject(
                USaveGameData::StaticClass()));
    }

    // Save player transform
    //CurrentSaveGame->PlayerTransform = PlayerTransform;

    // Let other systems save their data
    OnGameSaved.Broadcast(CurrentSaveGame);
    UE_LOG(LogTemp, Warning, TEXT(" OnGameSave Broadcast "));


    return UGameplayStatics::SaveGameToSlot(
        CurrentSaveGame,
        SaveSlot,
        UserIndex);
}


bool USaveManagerSubsystem::LoadGame()
{
    if (!UGameplayStatics::DoesSaveGameExist(
        SaveSlot,
        UserIndex))
    {
        return false;
    }

    CurrentSaveGame =
        Cast<USaveGameData>(
            UGameplayStatics::LoadGameFromSlot(
                SaveSlot,
                UserIndex));

    if (!CurrentSaveGame)
    {
        return false;
    }

    // Restore data here

    OnGameLoaded.Broadcast(CurrentSaveGame);

    UE_LOG(LogTemp, Warning, TEXT(" OnGameLoad Broadcast "));

    return true;
}


void USaveManagerSubsystem::SetSaveSlot(const FString& NewSlot)
{
    SaveSlot = NewSlot;
}

FString USaveManagerSubsystem::GetSaveSlot() const
{
    return SaveSlot;
}
