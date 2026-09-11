#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

UCLASS(BlueprintType)
class INVENTORYSYSTEM_API UItemData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:

    /** Display name */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FText ItemName;

    /** Item icon */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    TObjectPtr<UTexture2D> Icon;

    /** Maximum amount that can be stacked */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    int32 MaxStackSize = 1;

    /** Item description */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FText Description;
};