#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UInteractionComponent();

protected:

    virtual void BeginPlay() override;

public:

    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
    ) override;

    /**
     * Interact with the currently focused actor.
     */
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Interact();

    /**
     * Returns the actor currently being looked at.
     */
    UFUNCTION(BlueprintPure, Category = "Interaction")
    AActor* GetCurrentInteractable() const;

protected:

    /**
     * Maximum distance at which an actor can be interacted with.
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadOnly,
        Category = "Interaction"
    )
    float InteractionDistance = 300.f;

private:

    /**
     * Performs the interaction line trace
     * and updates the current interactable.
     */
    void UpdateInteractable();

    /**
     * Actor currently under the player's crosshair.
     */
    UPROPERTY()
    TObjectPtr<AActor> CurrentInteractable = nullptr;
};