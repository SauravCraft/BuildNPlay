// Fill out your copyright notice in the Description page of Project Settings.

#include "BNPPawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/InteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"

#include "Engine/CollisionProfile.h"

#include "Subsystems/SaveManagerSubsystem.h"
#include "SaveGames/SaveGameData.h"

#include "Subsystems/RespawnSubsystem.h"


// =========================================================
// CONSTRUCTOR
// =========================================================

ABNPPawn::ABNPPawn()
{
    PrimaryActorTick.bCanEverTick = false;


    // =====================================================
    // CAPSULE
    // =====================================================

    CapsuleComponent =
        CreateDefaultSubobject<UCapsuleComponent>(
            TEXT("Capsule"));


    // Make Capsule the root
    SetRootComponent(CapsuleComponent);


    // Capsule size
    CapsuleComponent->InitCapsuleSize(
        30.f,
        86.f);


    // Collision
    CapsuleComponent->SetCollisionProfileName(
        UCollisionProfile::Pawn_ProfileName);


    // Overlap
    CapsuleComponent->SetGenerateOverlapEvents(
        true);
}


// =========================================================
// BEGIN PLAY
// =========================================================

void ABNPPawn::BeginPlay()
{
    Super::BeginPlay();


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("BNPPawn BeginPlay")
    );


    // =====================================================
    // SAVE / LOAD SYSTEM
    // =====================================================

    if (UGameInstance* GameInstance =
        GetGameInstance())
    {
        USaveManagerSubsystem* Save =
            GameInstance->GetSubsystem<
            USaveManagerSubsystem>();


        if (Save)
        {
            // ---------------------------------------------
            // SAVE DELEGATE
            // ---------------------------------------------

            Save->OnGameSaved.AddUObject(
                this,
                &ABNPPawn::HandleSave);


            // ---------------------------------------------
            // LOAD DELEGATE
            // ---------------------------------------------

            Save->OnGameLoaded.AddUObject(
                this,
                &ABNPPawn::HandleLoad);


            UE_LOG(
                LogTemp,
                Warning,
                TEXT("BNPPawn: Save/Load Delegates Bound")
            );


            /*
             * IMPORTANT
             *
             * GameInstance can load the SaveGame before
             * BNPPawn is spawned.
             *
             * Therefore check whether SaveManager already
             * has loaded data.
             */

            if (USaveGameData* LoadedSave =
                Save->GetSaveGame())
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("BNPPawn: Existing Save Data Found")
                );


                HandleLoad(LoadedSave);
            }
        }
        else
        {
            UE_LOG(
                LogTemp,
                Error,
                TEXT("BNPPawn: SaveManagerSubsystem NOT FOUND")
            );
        }
    }


    // =====================================================
    // RESPawn DATA
    // =====================================================

    /*
     * We don't call RespawnSubsystem here.
     *
     * RespawnSubsystem is responsible for:
     *
     * - Checkpoints
     * - Active checkpoints
     * - Death respawn
     *
     * BNPPawn is responsible for:
     *
     * - Player transform save
     * - Player transform load
     */
}


// =========================================================
// END PLAY
// =========================================================

void ABNPPawn::EndPlay(
    const EEndPlayReason::Type EndPlayReason)
{
    /*
     * Remove delegates.
     *
     * This is important because your RespawnSubsystem
     * can destroy this Pawn and spawn a new one.
     */

    if (UGameInstance* GameInstance =
        GetGameInstance())
    {
        if (USaveManagerSubsystem* Save =
            GameInstance->GetSubsystem<
            USaveManagerSubsystem>())
        {
            Save->OnGameSaved.RemoveAll(this);

            Save->OnGameLoaded.RemoveAll(this);
        }
    }


    Super::EndPlay(EndPlayReason);
}


// =========================================================
// INPUT
// =========================================================

void ABNPPawn::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(
        PlayerInputComponent);


    UEnhancedInputComponent* EnhancedInput =
        Cast<UEnhancedInputComponent>(
            PlayerInputComponent);


    if (!EnhancedInput)
    {
        return;
    }


    // =====================================================
    // INTERACTION
    // =====================================================

    if (InteractAction)
    {
        EnhancedInput->BindAction(
            InteractAction,
            ETriggerEvent::Started,
            this,
            &ABNPPawn::interact);
    }
}


// =========================================================
// INTERACTION
// =========================================================

void ABNPPawn::interact()
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("BNPPawn: Interact Called")
    );


    UInteractionComponent* IC =
        FindComponentByClass<
        UInteractionComponent>();


    if (!IC)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("BNPPawn: InteractionComponent NOT FOUND")
        );

        return;
    }


    IC->Interact();
}


// =========================================================
// SAVE
// =========================================================

void ABNPPawn::HandleSave(
    USaveGameData* SaveGame)
{
    if (!SaveGame)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("BNPPawn HandleSave: SaveGame is NULL")
        );

        return;
    }


    /*
     * Save the complete Pawn transform.
     *
     * Includes:
     *
     * Location
     * Rotation
     * Scale
     */

    SaveGame->PlayerTransform =
        GetActorTransform();


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("BNPPawn PLAYER TRANSFORM SAVED: %s"),
        *GetActorLocation().ToString()
    );
}


// =========================================================
// LOAD
// =========================================================

void ABNPPawn::HandleLoad(
    USaveGameData* SaveGame)
{
    if (!SaveGame)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("BNPPawn HandleLoad: SaveGame is NULL")
        );

        return;
    }


    // =====================================================
    // VALIDATE TRANSFORM
    // =====================================================

    if (!SaveGame->PlayerTransform.IsValid())
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("BNPPawn: Saved Player Transform is INVALID")
        );

        return;
    }


    // =====================================================
    // RESTORE TRANSFORM
    // =====================================================

    SetActorTransform(
        SaveGame->PlayerTransform,
        false,
        nullptr,
        ETeleportType::TeleportPhysics);


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("BNPPawn PLAYER RESTORED TO: %s"),
        *GetActorLocation().ToString()
    );
}
