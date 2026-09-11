// Fill out your copyright notice in the Description page of Project Settings.


#include "BNPPawn.h"

// Sets default values
ABNPPawn::ABNPPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

