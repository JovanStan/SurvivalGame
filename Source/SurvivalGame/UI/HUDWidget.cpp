
#include "HUDWidget.h"
#include "../Inventory/ItemData.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UHUDWidget::UpdateEquippedItem(FItemData Item)
{
	if (EquippedItemText)
	{
		EquippedItemText->SetText(FText::FromString(Item.Name));
	}
	if (EquippedItemIcon)
	{
		EquippedItemIcon->SetBrushFromTexture(Item.Icon);
	}
}
