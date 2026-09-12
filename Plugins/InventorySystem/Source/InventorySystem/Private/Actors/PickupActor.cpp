#include "Actors/PickupActor.h"

#include "Components/SphereComponent.h"
#include "Components/HighlightableMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/InventoryComponent.h"

APickupActor::APickupActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // --------------------------------
    // Sphere
    // --------------------------------

    Sphere = CreateDefaultSubobject<USphereComponent>(
        TEXT("Sphere")
    );

    RootComponent = Sphere;

    Sphere->InitSphereRadius(50.f);

    Sphere->SetCollisionProfileName(
        TEXT("OverlapAllDynamic")
    );


    // --------------------------------
    // Highlightable Mesh
    // --------------------------------

    Mesh = CreateDefaultSubobject<UHighlightableMeshComponent>(
        TEXT("Mesh")
    );

    Mesh->SetupAttachment(RootComponent);


    // --------------------------------
    // Interaction Widget
    // --------------------------------

    InteractionWidget =
        CreateDefaultSubobject<UWidgetComponent>(
            TEXT("InteractionWidget")
        );

    InteractionWidget->SetupAttachment(RootComponent);

    InteractionWidget->SetRelativeLocation(
        FVector(0.f, 0.f, 100.f)
    );

    // Always faces player's screen
    InteractionWidget->SetWidgetSpace(
        EWidgetSpace::Screen
    );

    InteractionWidget->SetDrawSize(
        FVector2D(250.f, 60.f)
    );

    InteractionWidget->SetCollisionEnabled(
        ECollisionEnabled::NoCollision
    );

    // DON'T set WidgetClass here
    // InteractionWidgetClass will be assigned from Blueprint

    InteractionWidget->SetVisibility(false);
}

// --------------------------------
// Begin Play
// --------------------------------

void APickupActor::BeginPlay()
{
    Super::BeginPlay();

    if (InteractionWidget)
    {
        // Set Blueprint widget class AFTER Blueprint defaults exist
        if (InteractionWidgetClass)
        {
            InteractionWidget->SetWidgetClass(
                InteractionWidgetClass
            );
        }

        InteractionWidget->SetVisibility(false);
    }
}


void APickupActor::Interact_Implementation(AActor* Interactor)
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
        Mesh->Highlight();
    }

    if (InteractionWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UI ON"));
        InteractionWidget->SetVisibility(true);
    }
}

void APickupActor::UnHighlight_Implementation()
{
    if (Mesh)
    {
        Mesh->UnHighlight();
    }

    if (InteractionWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UI OFF"));
        InteractionWidget->SetVisibility(false);
    }
}

