// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DeathBox.h"
#include "Subsystems/RespawnSubsystem.h"
#include "Components/BoxComponent.h"

// Sets default values
ADeathBox::ADeathBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionBox =
        CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

    RootComponent = CollisionBox;

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);

}

void ADeathBox::Die(AActor* DieActor)
{
    if (URespawnSubsystem* RespawnSubsystem =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>())
    {

        APawn* Pawn = Cast<APawn>(DieActor);

        if (!Pawn || !Pawn->IsPlayerControlled())
        {
            return;
        }

        RespawnSubsystem->RespawnPlayer(Pawn, RespawnSubsystem->GetCurrentCheckpoint());

    }
}

// Called when the game starts or when spawned
void ADeathBox::BeginPlay()
{
	Super::BeginPlay();
	
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathBox::OnOverlapBegin);

}

void ADeathBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Call Death in Character

    if (!OtherActor)
    {
        return;
    }

    Die(OtherActor);

    UE_LOG(LogTemp, Warning, TEXT("Death Box Hit!"));

}


