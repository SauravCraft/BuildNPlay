#include "Components/RespawnComponent.h"
#include "Engine/GameInstance.h"
#include "Subsystems/RespawnSubsystem.h"

#include "GameFramework/Pawn.h"

URespawnComponent::URespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URespawnComponent::BeginPlay()
{
    Super::BeginPlay();

    RespawnSubsystem =
        GetWorld()->GetGameInstance()->GetSubsystem<URespawnSubsystem>();
}

void URespawnComponent::RespawnOwner()
{
    UE_LOG(LogTemp, Warning, TEXT("Respawn Component Call"));

    if (!RespawnSubsystem)
    {
        return;
    }

    APawn* Pawn = Cast<APawn>(GetOwner());

    if (!Pawn)
    {
        return;
    }

    RespawnSubsystem->RespawnPlayer(Pawn,GetOwner()->GetActorTransform());
    UE_LOG(LogTemp, Warning, TEXT("Respawn Component Called"));

}