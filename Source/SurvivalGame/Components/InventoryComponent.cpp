
#include "InventoryComponent.h"

#include "../Player/SurvivalPlayerController.h"
#include "../UI/HUDWidget.h"
#include "Crafting/Recipe.h"
#include "Kismet/GameplayStatics.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	SurvivalPlayerController = Cast<ASurvivalPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

}

bool UInventoryComponent::CanCraftItem(FItemData ItemData)
{
	for (FRecipe Resource : ItemData.ResourcesNeeded)
	{
		FItemData* Row = Resource.Item.GetRow<FItemData>(TEXT("CanCraftItem"));
		if (!Row) return false;
		
		bool bHasEnough = false;
		for (auto& Item : Items)
		{
			if (Item.Name == Row->Name && Item.Amount >= Resource.Amount)
			{
				bHasEnough = true;
				break;
			}
		}
		if (!bHasEnough) return false;
	}
	return true;
}

void UInventoryComponent::AddItem(const FItemData& NewItem)
{
	for (auto& Item : Items)
	{
		if (Item.Name == NewItem.Name)
		{
			Item.Amount += NewItem.Amount;
			SurvivalPlayerController->GetHUDWidget()->AddItemNotifications(Item.Name, Item.Icon, NewItem.Amount);
			return;
		}
	}
	Items.Add(NewItem);
	SurvivalPlayerController->GetHUDWidget()->AddItemNotifications(NewItem.Name, NewItem.Icon, NewItem.Amount);
}

void UInventoryComponent::RemoveItem(const FItemData& NewItem, bool bDecreaseOneOnly)
{
	for (auto& Item : Items)
	{
		if (Item.Name != NewItem.Name) continue;
		
		Item.Amount -= bDecreaseOneOnly ? 1 : NewItem.Amount;
		if (Item.Amount <= 0)
		{
			const int Index = static_cast<int>(&Item - Items.GetData());
			Items.RemoveAt(Index);
		}
		return;
	}
}

int UInventoryComponent::GetItemAmount(const FItemData& ItemData)
{
	for (const FItemData& Item : Items)
	{
		if (Item.Name == ItemData.Name) return Item.Amount;
	}
	return 0;
}


