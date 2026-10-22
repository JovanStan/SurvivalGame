
#include "HUDWidget.h"
#include "../Inventory/Item.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UHUDWidget::UpdateEquippedItem(FItem Item)
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
