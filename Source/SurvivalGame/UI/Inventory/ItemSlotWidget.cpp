
#include "ItemSlotWidget.h"

#include "../HUDWidget.h"
#include "../../Characters/SurvivalCharacter.h"
#include "../../Components/InventoryComponent.h"
#include "../../Player/SurvivalPlayerController.h"
#include "Components/BuildingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ItemButton->OnPressed.AddDynamic(this, &ThisClass::OnItemButtonPressed);
	ItemButton->OnHovered.AddDynamic(this, &ThisClass::OnItemButtonHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &ThisClass::OnItemButtonUnhovered);
	
	GetWorld()->GetTimerManager().SetTimer(StartDelayTimerHandle, this, &UItemSlotWidget::StartDelay, 0.1f, false);
}

void UItemSlotWidget::SetItem(const FItemData& NewItem, int32 Amount)
{
	Item = NewItem;
	Item.Amount = Amount;
	if (IconImage)
	{
		IconImage->SetBrushFromTexture(Item.Icon);
	}
	if (AmountText)
	{
		AmountText->SetText(FText::AsNumber(Amount));
	}
}

void UItemSlotWidget::StartDelay()
{
	if (AmountText)
	{
		AmountText->SetText(FText::AsNumber(Item.Amount));
	}
	
	if (IconImage)
	{
		IconImage->SetBrushFromTexture(Item.Icon);
	}
	
}

void UItemSlotWidget::OnItemButtonPressed()
{
	if (ASurvivalCharacter* PlayerCharacter = Cast<ASurvivalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		PlayerCharacter->GetInventoryComponent()->EquippedItem = Item;
		PlayerCharacter->EquipItemMesh(Item);
		SetSelected();
		if (ASurvivalPlayerController* PC = Cast<ASurvivalPlayerController>(PlayerCharacter->GetController()))
		{
			PC->CloseInventory();
			PC->GetHUDWidget()->UpdateEquippedItem(Item);
		}
		if (PlayerCharacter->GetInventoryComponent()->EquippedItem.Name == "Axe" || PlayerCharacter->GetInventoryComponent()->EquippedItem.Name == "Pickaxe")
		{
			PlayerCharacter->GetBuildingComponent()->StopBuildMode();
		}
		else
		{
			PlayerCharacter->GetBuildingComponent()->StopBuildMode();
			PlayerCharacter->GetBuildingComponent()->BuildMode();
		}
	}
}

void UItemSlotWidget::OnItemButtonHovered()
{
	OnSlotHovered.ExecuteIfBound(Item);
}

void UItemSlotWidget::OnItemButtonUnhovered()
{
	OnSlotUnhovered.ExecuteIfBound();
}

void UItemSlotWidget::SetSelected()
{
	FButtonStyle SelectedStyle;
	FSlateBrush SelectedBrush;
	SelectedBrush.TintColor = FLinearColor::Green;

	SelectedStyle.SetNormal(SelectedBrush);
	ItemButton->SetStyle(SelectedStyle);
}
