// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interactable.h"
#include "Components/StaticMeshComponent.h"
#include "HighlightableMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class UHighlightableMeshComponent : public UStaticMeshComponent, public IInteractable
{
	GENERATED_BODY()

public:

    UHighlightableMeshComponent();

    UFUNCTION(BlueprintCallable)
    virtual void Highlight_Implementation() override;

    UFUNCTION(BlueprintCallable)
    virtual void UnHighlight_Implementation() override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Highlight")
    TObjectPtr<UMaterialInterface> HighlightMaterial;

};
