#include "BNPGameInstance.h"
#include "Subsystems/SaveManagerSubsystem.h"

void UBNPGameInstance::Init()
{
    Super::Init();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("BNP GameInstance Initialized")
    );

    if (USaveManagerSubsystem* SaveSubsystem =
        GetSubsystem<USaveManagerSubsystem>())
    {
        SaveSubsystem->LoadGame();
    }
    else
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("SaveSubsystem NULL")
        );
    }
}

void UBNPGameInstance::Shutdown()
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("BNP GameInstance Shutdown Start")
    );

    if (USaveManagerSubsystem* SaveSubsystem =
        GetSubsystem<USaveManagerSubsystem>())
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Calling SaveGame")
        );

        SaveSubsystem->SaveGame();
    }
    else
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("SaveSubsystem NULL")
        );
    }

    Super::Shutdown();
}