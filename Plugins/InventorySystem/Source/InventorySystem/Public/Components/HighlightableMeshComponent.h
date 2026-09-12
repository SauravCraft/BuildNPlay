#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "HighlightableMeshComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UHighlightableMeshComponent
    : public UStaticMeshComponent
{
    GENERATED_BODY()

public:

    UHighlightableMeshComponent();

    /** Enable highlight */
    UFUNCTION(BlueprintCallable, Category = "Highlight")
    void Highlight();

    /** Disable highlight */
    UFUNCTION(BlueprintCallable, Category = "Highlight")
    void UnHighlight();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Highlight")
    TObjectPtr<UMaterialInterface> HighlightMaterial;
};