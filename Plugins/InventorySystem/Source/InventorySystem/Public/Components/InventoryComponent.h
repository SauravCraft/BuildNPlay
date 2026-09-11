#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemData;

USTRUCT(BlueprintType)
struct FInventoryItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UItemData> ItemData = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Quantity = 0;
};

UCLASS(ClassGroup = (Inventory), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UInventoryComponent();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(
        UItemData* ItemData,
        int32 Quantity
    );

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(
        UItemData* ItemData,
        int32 Quantity
    );

    UFUNCTION(BlueprintPure, Category = "Inventory")
    bool HasItem(
        UItemData* ItemData,
        int32 Quantity
    ) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    const TArray<FInventoryItem>& GetItems() const
    {
        return Items;
    }

protected:

    virtual void BeginPlay() override;

private:

    UPROPERTY()
    TArray<FInventoryItem> Items;
};