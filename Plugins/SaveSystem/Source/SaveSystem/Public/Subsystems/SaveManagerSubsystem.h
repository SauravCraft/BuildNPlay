#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManagerSubsystem.generated.h"

class USaveGameData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameSave, class USaveGameData*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameLoad, class USaveGameData*);

UCLASS()
class SAVESYSTEM_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    bool SaveGame();
    bool LoadGame();


    void SetSaveSlot(const FString& NewSlot);
    FString GetSaveSlot() const;

    FORCEINLINE USaveGameData* GetSaveGame() const
    {
        return CurrentSaveGame;
    }

    FOnGameSave OnGameSaved;
    FOnGameLoad OnGameLoaded;

private:

    UPROPERTY()
    TObjectPtr<USaveGameData> CurrentSaveGame;

    UPROPERTY()
    FString SaveSlot = TEXT("SaveSlot");

    UPROPERTY()
    int32 UserIndex = 0;


};