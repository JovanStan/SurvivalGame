
#include "InventoryComponent.h"

#include "../Player/SurvivalPlayerController.h"
#include "../UI/HUDWidget.h"
#include "Kismet/GameplayStatics.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SurvivalPlayerController = Cast<ASurvivalPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	FItemData Item("Wood", 3, nullptr, nullptr, false);
	FItemData Item2("Stone", 2, nullptr, nullptr, false);
	AddItem(Item);
	AddItem(Item2);
	//RemoveItem(Item, false);
}

void UInventoryComponent::AddItem(const FItemData& NewItem)
{
	for (auto& Item : Items)
	{
		if (Item.Name == NewItem.Name)
		{
			Item.Amount += NewItem.Amount;
			SurvivalPlayerController->GetHUDWidget()->AddItemNotifications(Item.Name, Item.Icon, Item.Amount);
			return;
		}
	}
	Items.Add(NewItem);
	SurvivalPlayerController->GetHUDWidget()->AddItemNotifications(NewItem.Name, NewItem.Icon, NewItem.Amount);
}

bool UInventoryComponent::RemoveItem(const FItemData& NewItem, bool bDecreaseOneOnly)
{
	for (auto& Item : Items)
	{
		if (Item.Name != NewItem.Name) continue;
		
		Item.Amount -= bDecreaseOneOnly ? 1 : NewItem.Amount;
		if (Item.Amount <= 0)
		{
			const int32 Index = static_cast<int32>(&Item - Items.GetData());
			Items.RemoveAt(Index);
			return true;
		}
		return false;
	}
	return false;
}

