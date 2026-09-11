#include "Actors/PickupActor.h"
#include "Components/SphereComponent.h"
#include "Components/HighlightableMeshComponent.h"
#include "Components/InventoryComponent.h"

APickupActor::APickupActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Sphere = CreateDefaultSubobject<USphereComponent>(
        TEXT("Sphere")
    );

    RootComponent = Sphere;

    Sphere->InitSphereRadius(50.f);

    Sphere->SetCollisionProfileName(
        TEXT("OverlapAllDynamic")
    );

    Mesh = CreateDefaultSubobject<UHighlightableMeshComponent>(
        TEXT("Mesh")
    );

    Mesh->SetupAttachment(RootComponent);
}

void APickupActor::Interact_Implementation(
    AActor* Interactor)
{
    if (!Interactor || !ItemData || Quantity <= 0)
    {
        return;
    }

    UInventoryComponent* Inventory =
        Interactor->FindComponentByClass<UInventoryComponent>();

    if (!Inventory)
    {
        return;
    }

    if (Inventory->AddItem(ItemData, Quantity))
    {
        Destroy();
    }
}

void APickupActor::Highlight_Implementation()
{
    if (Mesh)
    {
        IInteractable::Execute_Highlight(Mesh);
    }
}

void APickupActor::UnHighlight_Implementation()
{
    if (Mesh)
    {
        IInteractable::Execute_UnHighlight(Mesh);
    }
}