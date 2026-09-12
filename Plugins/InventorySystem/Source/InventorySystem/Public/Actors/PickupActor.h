#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "PickupActor.generated.h"

class UHighlightableMeshComponent;
class USphereComponent;
class UWidgetComponent;
class UUserWidget;
class UItemData;

UCLASS()
class INVENTORYSYSTEM_API APickupActor
    : public AActor
    , public IInteractable
{
    GENERATED_BODY()

public:

    APickupActor();
    
    virtual void BeginPlay() override;

    // Interaction
    virtual void Interact_Implementation(AActor* Interactor) override;

    // Highlight / interaction prompt
    virtual void Highlight_Implementation() override;
    virtual void UnHighlight_Implementation() override;

protected:

    /** Pickup collision */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USphereComponent> Sphere;

    /** Pickup mesh */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UHighlightableMeshComponent> Mesh;

    /** Interaction prompt */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
    TObjectPtr<UWidgetComponent> InteractionWidget;

    /** Widget Blueprint */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
    TSubclassOf<UUserWidget> InteractionWidgetClass;

    /** Item definition */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<UItemData> ItemData;

    /** Stack quantity */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    int32 Quantity = 1;
};