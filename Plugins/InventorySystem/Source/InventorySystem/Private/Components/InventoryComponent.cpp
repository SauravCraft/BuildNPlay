#include "Components/InventoryComponent.h"
#include "Data/ItemData.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

bool UInventoryComponent::AddItem(
    UItemData* ItemData,
    int32 Quantity)
{
    if (!ItemData || Quantity <= 0)
    {
        return false;
    }

    // Try to stack with an existing item
    for (FInventoryItem& InventoryItem : Items)
    {
        if (InventoryItem.ItemData == ItemData)
        {
            InventoryItem.Quantity += Quantity;

            return true;
        }
    }

    // Create a new inventory entry
    FInventoryItem NewItem;

    NewItem.ItemData = ItemData;
    NewItem.Quantity = Quantity;

    Items.Add(NewItem);

    return true;
}

bool UInventoryComponent::RemoveItem(
    UItemData* ItemData,
    int32 Quantity)
{
    if (!ItemData || Quantity <= 0)
    {
        return false;
    }

    for (int32 i = 0; i < Items.Num(); ++i)
    {
        FInventoryItem& InventoryItem = Items[i];

        if (InventoryItem.ItemData == ItemData)
        {
            if (InventoryItem.Quantity < Quantity)
            {
                return false;
            }

            InventoryItem.Quantity -= Quantity;

            if (InventoryItem.Quantity <= 0)
            {
                Items.RemoveAt(i);
            }

            return true;
        }
    }

    return false;
}

bool UInventoryComponent::HasItem(
    UItemData* ItemData,
    int32 Quantity) const
{
    if (!ItemData || Quantity <= 0)
    {
        return false;
    }

    for (const FInventoryItem& InventoryItem : Items)
    {
        if (InventoryItem.ItemData == ItemData)
        {
            return InventoryItem.Quantity >= Quantity;
        }
    }

    return false;
}