// Fill out your copyright notice in the Description page of Project Settings.


#include "BNPPawn.h"
#include "Components/InteractionComponent.h"
#include "EnhancedInputComponent.h"


// Sets default values
ABNPPawn::ABNPPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsules
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));

	// Make it the Root
	SetRootComponent(CapsuleComponent);

	// Size
	CapsuleComponent->InitCapsuleSize(30.f, 86.f);

	// Collision
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	// Optional
	CapsuleComponent->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ABNPPawn::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ABNPPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABNPPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedInput) return;



	// Binding Input Function 

	EnhancedInput->BindAction(
		InteractAction,
		ETriggerEvent::Started,
		this,
		&ABNPPawn::interact);

}

void ABNPPawn::interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact Called"));

	UInteractionComponent* IC =
		FindComponentByClass<UInteractionComponent>();

	if (!IC)
	{
		return;
	}

	IC->Interact();
}
