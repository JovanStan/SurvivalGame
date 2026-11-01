
#include "ResourceSlot.h"

#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UResourceSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetWorld()->GetTimerManager().SetTimer(StartDelayTimerHandle, this, &UResourceSlot::StartDelay, 0.1f, false);
}

void UResourceSlot::SetResource(const FItemData& NewItem, int32 Amount)
{
	Item = NewItem;
	ItemAmount = Amount;

	if (IconImage)
	{
		IconImage->SetBrushFromTexture(Item.Icon);
	}

	if (AmountText)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("Name"), FText::FromString(Item.Name));
		Args.Add(TEXT("Amount"), Amount);
		AmountText->SetText(FText::Format(NSLOCTEXT("Resource", "NameAmount", "{Name}: {Amount}"), Args));
	}
}

void UResourceSlot::StartDelay()
{
	if (AmountText)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("Name"), FText::FromString(Item.Name));
		Args.Add(TEXT("Amount"), ItemAmount);

		AmountText->SetText(FText::Format(
			NSLOCTEXT("ItemSlot", "NameAmount", "{Name}: {Amount}"), Args));
	}
	if (IconImage)
	{
		IconImage->SetBrushFromTexture(Item.Icon);
	}
}
