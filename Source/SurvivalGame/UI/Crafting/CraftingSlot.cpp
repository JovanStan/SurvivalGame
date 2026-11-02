
#include "CraftingSlot.h"

#include "../../Characters/SurvivalCharacter.h"
#include "../../Components/InventoryComponent.h"
#include "../../Player/SurvivalPlayerController.h"
#include "../Inventory/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Image.h"

void UCraftingSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	ItemButton->OnPressed.AddDynamic(this, &ThisClass::ItemButtonPressed);
	
	GetWorld()->GetTimerManager().SetTimer(StartDelayTimerHandle, this, &UCraftingSlot::StartDelay, 0.1f, false);
}

void UCraftingSlot::SetCraftingItem(const FItemData& NewItem)
{
	Item = NewItem;
	if (IconImage)
	{
		IconImage->SetBrushFromTexture(Item.Icon);
	}
}

void UCraftingSlot::StartDelay()
{
	if (IconImage)
	{
		IconImage->SetBrushFromTexture(Item.Icon);
	}
	
	Inventory = Cast<ASurvivalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetInventoryComponent();
	
	// This part should be optimized, because its going to cast for every crafting slot
	if (Inventory)
	{
		if (Inventory->CanCraftItem(Item))
		{
			SetSelected(FLinearColor::Green);
		}
		else
		{
			SetSelected(FLinearColor::Gray);
		}
	}
}

void UCraftingSlot::ItemButtonPressed()
{
	if (ASurvivalPlayerController* SurvivalPlayerController = Cast<ASurvivalPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		SurvivalPlayerController->GetInventoryWidget()->DisplayCraftingResources(Item.ResourcesNeeded, Item);
	}
}

void UCraftingSlot::SetSelected(const FLinearColor LinearColor)
{
	FButtonStyle SelectedStyle;
	FSlateBrush SelectedBrush;
	SelectedBrush.TintColor = LinearColor;

	SelectedStyle.SetNormal(SelectedBrush);
	ItemButton->SetStyle(SelectedStyle);
}
