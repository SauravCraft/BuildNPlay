// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HighlightableMeshComponent.h"

UHighlightableMeshComponent::UHighlightableMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHighlightableMeshComponent::Highlight_Implementation()
{
    SetOverlayMaterial(HighlightMaterial);
}

void UHighlightableMeshComponent::UnHighlight_Implementation()
{
    SetOverlayMaterial(nullptr);
}