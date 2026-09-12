#include "Components/HighlightableMeshComponent.h"

UHighlightableMeshComponent::UHighlightableMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHighlightableMeshComponent::Highlight()
{
    if (HighlightMaterial)
    {
        SetOverlayMaterial(HighlightMaterial);
    }
}

void UHighlightableMeshComponent::UnHighlight()
{
    SetOverlayMaterial(nullptr);
}