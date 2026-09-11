// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InteractionComponent.h"

#include "Interfaces/Interactable.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UInteractionComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(
        DeltaTime,
        TickType,
        ThisTickFunction
    );

    UpdateInteractable();
}

void UInteractionComponent::UpdateInteractable()
{
    APawn* Pawn = Cast<APawn>(GetOwner());

    if (!Pawn)
    {
        return;
    }

    APlayerController* PC =
        Cast<APlayerController>(Pawn->GetController());

    if (!PC)
    {
        return;
    }

    int32 ViewportX = 0;
    int32 ViewportY = 0;

    PC->GetViewportSize(
        ViewportX,
        ViewportY
    );

    FVector WorldLocation;
    FVector WorldDirection;

    if (!PC->DeprojectScreenPositionToWorld(
        ViewportX * 0.5f,
        ViewportY * 0.5f,
        WorldLocation,
        WorldDirection))
    {
        return;
    }

    const FVector Start = WorldLocation;

    const FVector End =
        Start + WorldDirection * InteractionDistance;

    FHitResult Hit;

    FCollisionQueryParams Params;

    Params.AddIgnoredActor(Pawn);

    const bool bHit =
        GetWorld()->LineTraceSingleByChannel(
            Hit,
            Start,
            End,
            ECC_Visibility,
            Params
        );

    AActor* NewInteractable = nullptr;

    if (bHit)
    {
        AActor* HitActor = Hit.GetActor();

        if (IsValid(HitActor) && HitActor->Implements<UInteractable>())
        {
            NewInteractable = HitActor;
        }
    }

    if (NewInteractable == CurrentInteractable)
    {
        return;
    }

    if (IsValid(CurrentInteractable))
    {
        IInteractable::Execute_UnHighlight(CurrentInteractable);
    }

    CurrentInteractable = NewInteractable;

    if (IsValid(CurrentInteractable))
    {
        IInteractable::Execute_Highlight(CurrentInteractable);
    }
}

void UInteractionComponent::Interact()
{
    if (!IsValid(CurrentInteractable))
    {
        CurrentInteractable = nullptr;
        return;
    }

    IInteractable::Execute_Interact(CurrentInteractable, GetOwner());

    // The interactable may have destroyed itself as a result (e.g. pickup consumed).
    if (!IsValid(CurrentInteractable))
    {
        CurrentInteractable = nullptr;
    }
}

AActor* UInteractionComponent::GetCurrentInteractable() const
{
    return CurrentInteractable;
}