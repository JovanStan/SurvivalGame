
#include "InventoryWidget.h"

#include "ItemsGridWidget.h"
#include "../../Characters/SurvivalCharacter.h"
#include "../../Components/InventoryComponent.h"
#include "ItemSlotWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/UniformGridPanel.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ASurvivalCharacter* PlayerCharacter =  Cast<ASurvivalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		int32 Index = 0;
		for (auto& Item : PlayerCharacter->GetInventoryComponent()->GetItems())
		{
			UItemSlotWidget* ItemSlot = CreateWidget<UItemSlotWidget>(this, ItemSlotClass);
			const int32 Row = Index / SlotsPerRow;
			const int32 Column = Index % SlotsPerRow;
			ItemSlot->Item = Item;
			
			ItemSlot->OnSlotHovered.BindUObject(this, &ThisClass::HandleSlotHovered);
			ItemSlot->OnSlotUnhovered.BindUObject(this, &ThisClass::HideItemInfo);
			
			ItemsGrid->GridPanel->AddChildToUniformGrid(ItemSlot, Row, Column);
			++Index;
		}
		
		SetSelected();
	}
}

void UInventoryWidget::ShowItemInfo(FItem ItemHovered, bool bShowAmount)
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Name"), FText::FromString(ItemHovered.Name));
	Args.Add(TEXT("Amount"), ItemHovered.Amount);

	const FText Result = bShowAmount
		? FText::Format(NSLOCTEXT("Inventory", "ItemInfoAmount", "{Name}: {Amount}"), Args)
		: FText::FromString(ItemHovered.Name);

	ItemInfoText->SetText(Result);
	TooltipPosition(); 
	ItemInfoPanel->SetVisibility(ESlateVisibility::HitTestInvisible);

	GetWorld()->GetTimerManager().SetTimer(TooltipPositionTimerHandle, this, &ThisClass::TooltipPosition, 0.01f, true);
}

void UInventoryWidget::HideItemInfo()
{
	ItemInfoPanel->SetVisibility(ESlateVisibility::Hidden);
	GetWorld()->GetTimerManager().ClearTimer(TooltipPositionTimerHandle);
}

void UInventoryWidget::TooltipPosition()
{
	if (!ItemInfoPanel) return;
	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(ItemInfoPanel->Slot))
	{
		CanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 0.f, 0.f));
		CanvasSlot->SetAlignment(FVector2D::ZeroVector);

		const FVector2D MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		CanvasSlot->SetPosition(MousePos + FVector2D(10.f, 10.f));
	}
}

void UInventoryWidget::HandleSlotHovered(const FItem& ItemHovered)
{
	ShowItemInfo(ItemHovered, true);
}
