
#include "InventoryWidget.h"

#include "ItemsGridWidget.h"
#include "../../Characters/SurvivalCharacter.h"
#include "../../Components/InventoryComponent.h"
#include "ItemSlotWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/UniformGridPanel.h"
#include "UI/Crafting/CraftingSlot.h"
#include "UI/Crafting/CraftingWidget.h"
#include "UI/Crafting/ResourceSlot.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CraftButton->OnPressed.AddDynamic(this, &ThisClass::CraftButtonPressed);
	
	UpdateInventory();
}

void UInventoryWidget::ShowItemInfo(FItemData ItemHovered, bool bShowAmount)
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

void UInventoryWidget::UpdateInventory()
{
	ItemsGrid->GridPanel->ClearChildren();
	
	if (ASurvivalCharacter* PlayerCharacter =  Cast<ASurvivalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		// Update items that we have in Inventory
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
		
		CraftItemsGrid->GridPanel->ClearChildren();
		CraftableItemsList.Empty();
	
		// Create Crafting slots
		if (UDataTable* Table = PlayerCharacter->GetInventoryComponent()->GetItemsDataTable())
		{
			for (const FName& RowName : Table->GetRowNames())
			{
				const FItemData* Row = Table->FindRow<FItemData>(RowName, TEXT("Loop items"));
				if (!Row) continue;
			
				if (Row->bCanCraft)
				{
					CraftableItemsList.Add(*Row);
				}
			}
			int32 Index2 = 0;
			for (auto& Item : CraftableItemsList)
			{
				UCraftingSlot* CraftingSlot = CreateWidget<UCraftingSlot>(this, CraftingSlotClass);
				CraftingSlot->Item = Item;
				const int32 Row = Index2 / SlotsPerRow;
				const int32 Column = Index2 % SlotsPerRow;
				CraftItemsGrid->GridPanel->AddChildToUniformGrid(CraftingSlot, Row, Column);
				++Index2;
			}
		}
	}
}

void UInventoryWidget::HandleSlotHovered(const FItemData& ItemHovered)
{
	ShowItemInfo(ItemHovered, true);
}

void UInventoryWidget::DisplayCraftingResources(TArray<FRecipe> Resources, FItemData ItemToCraft)
{
	CraftingWidget->VerticalBox->ClearChildren();
	
	for (auto& Resource : Resources)
	{
		FItemData* Row = Resource.Item.GetRow<FItemData>(TEXT("DisplayCraftingResources"));
		if (!Row) return;
		
		UResourceSlot* ResourceSlot = CreateWidget<UResourceSlot>(this, ResourceSlotClass);
		ResourceSlot->SetResource(*Row, Resource.Amount);
		ResourceSlot->SetPadding(FMargin(5.f, 5.f, 5.f, 0.f));
		CraftingWidget->VerticalBox->AddChild(ResourceSlot);
	}
	
	ItemToCraftSelected = ItemToCraft;
	CraftButton->SetVisibility(ESlateVisibility::Visible);
	CraftingWidget->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryWidget::CraftButtonPressed()
{
	// This part should be optimized
	if ((Inventory = Cast<ASurvivalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetInventoryComponent()))
	{
		if (Inventory->CanCraftItem(ItemToCraftSelected))
		{
			Inventory->AddItem(ItemToCraftSelected);
			for (auto& Resource : ItemToCraftSelected.ResourcesNeeded)
			{
				FItemData* Row = Resource.Item.GetRow<FItemData>(TEXT("CraftButtonPressed"));
				if (!Row) return;
				
				FItemData ToRemove = *Row;
				ToRemove.Amount = Resource.Amount;
				Inventory->RemoveItem(ToRemove, false);
			}
			UpdateInventory();
		}
	}
}
