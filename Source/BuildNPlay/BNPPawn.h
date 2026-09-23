// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BNPPawn.generated.h"

class UCapsuleComponent;
class UInputAction;
class USaveGameData;

UCLASS()
class BUILDNPLAY_API ABNPPawn : public APawn
{
    GENERATED_BODY()

public:

    ABNPPawn();

protected:

    virtual void BeginPlay() override;

    virtual void EndPlay(
        const EEndPlayReason::Type EndPlayReason) override;

    virtual void SetupPlayerInputComponent(
        UInputComponent* PlayerInputComponent) override;


    // =========================================================
    // INPUT
    // =========================================================

    void interact();


    // =========================================================
    // SAVE / LOAD
    // =========================================================

    void HandleSave(
        USaveGameData* SaveGame);

    void HandleLoad(
        USaveGameData* SaveGame);


public:

    // =========================================================
    // COMPONENTS
    // =========================================================

    UPROPERTY(
        VisibleAnywhere,
        BlueprintReadOnly,
        Category = "Components")
    UCapsuleComponent* CapsuleComponent;


    // =========================================================
    // INPUT ACTION
    // =========================================================

    UPROPERTY(
        EditAnywhere,
        BlueprintReadOnly,
        Category = "Input")
    UInputAction* InteractAction;
};