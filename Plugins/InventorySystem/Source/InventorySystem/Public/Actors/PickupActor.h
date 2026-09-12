#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "PickupActor.generated.h"

class USphereComponent;
class UHighlightableMeshComponent;
class UItemData;

UCLASS()
class INVENTORYSYSTEM_API APickupActor
    : public AActor
    , public IInteractable
{
    GENERATED_BODY()

public:

    APickupActor();

    virtual void Interact_Implementation(
        AActor* Interactor
    ) override;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USphereComponent> Sphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UHighlightableMeshComponent> Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<UItemData> ItemData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    int32 Quantity = 1;
};