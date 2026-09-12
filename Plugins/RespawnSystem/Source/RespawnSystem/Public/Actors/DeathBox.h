// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathBox.generated.h"


class UBoxComponent;

UCLASS()
class RESPAWNSYSTEM_API ADeathBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathBox();

    void Die(AActor* DieActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UBoxComponent> CollisionBox;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );


};
