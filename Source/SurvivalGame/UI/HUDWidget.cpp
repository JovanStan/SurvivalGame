
#include "HUDWidget.h"
#include "../Inventory/ItemData.h"
#include "Characters/SurvivalCharacter.h"
#include "Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"


void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SurvivalCharacter = Cast<ASurvivalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (SurvivalCharacter && !SurvivalCharacter->GetInventoryComponent()->EquippedItem.Name.IsEmpty())
	{
		UpdateEquippedItem(SurvivalCharacter->GetInventoryComponent()->EquippedItem);
	}
	else
	{
		EquippedItemText->SetVisibility(ESlateVisibility::Hidden);
		EquippedItemIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UHUDWidget::UpdateEquippedItem(FItemData Item)
{
	if (EquippedItemText)
	{
		EquippedItemText->SetVisibility(ESlateVisibility::Visible);
		EquippedItemText->SetText(FText::FromString(Item.Name));
	}
	if (EquippedItemIcon)
	{
		EquippedItemIcon->SetVisibility(ESlateVisibility::Visible);
		EquippedItemIcon->SetBrushFromTexture(Item.Icon);
	}
}
