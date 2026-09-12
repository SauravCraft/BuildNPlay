#include "Actors/CheckpointBox.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Subsystems/RespawnSubsystem.h"

ACheckpointBox::ACheckpointBox()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

    RootComponent = BoxComponent;

    BoxComponent->SetCollisionProfileName(TEXT("Trigger"));


}

void ACheckpointBox::OnCheckpointLoaded()
{
    UE_LOG(LogTemp, Warning,
        TEXT("Refresh %s"),
        *CheckPointId.ToString());

    URespawnSubsystem* Respawn =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>();

    if (!Respawn)
    {
        return;
    }

    bIsActivated =
        Respawn->IsCheckpointActivated(CheckPointId);

    UE_LOG(LogTemp, Warning,
        TEXT("%s = %d"),
        *CheckPointId.ToString(),
        bIsActivated);
}

void ACheckpointBox::BeginPlay()
{
    Super::BeginPlay();

    if (URespawnSubsystem* Respawn =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>())
    {
        Respawn->OnCheckpointLoaded.AddUObject(
            this,
            &ACheckpointBox::OnCheckpointLoaded);
    }

    BoxComponent->OnComponentBeginOverlap.AddDynamic(
        this,
        &ACheckpointBox::OnCheckpointBeginOverlap);
}

void ACheckpointBox::OnCheckpointBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    APawn* Pawn = Cast<APawn>(OtherActor);

    if (!Pawn || !Pawn->IsPlayerControlled() || bIsActivated)
    {
        UE_LOG(LogTemp, Warning, TEXT("1"));

        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("2"));
    URespawnSubsystem* Respawn =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>();

    if (!Respawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("3"));

        return;
    }

    if (Respawn->IsCheckpointActivated(CheckPointId))
    {
        UE_LOG(LogTemp, Warning, TEXT("4"));

        return;

    }

    Respawn->ActivateCheckpoint(CheckPointId);
    UE_LOG(LogTemp, Warning, TEXT("5"));

    bIsActivated = true;
    UE_LOG(LogTemp, Warning, TEXT("6"));

    Respawn->SetCheckpoint(Pawn->GetActorTransform());


    UE_LOG(LogTemp, Warning,
        TEXT("Checkpoint %s Activated"),
        *CheckPointId.ToString());
}