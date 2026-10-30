
#include "ItemSlotWidget.h"

#include "../HUDWidget.h"
#include "../../Characters/SurvivalCharacter.h"
#include "../../Components/InventoryComponent.h"
#include "../../Player/SurvivalPlayerController.h"
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

void UItemSlotWidget::StartDelay()
{
	if (AmountText)
	{
		AmountText->SetText(FText::FromString(Item.Name));
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
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Equipped %s"), *Item.Name));
		PlayerCharacter->EquipItemMesh(Item);
		SetSelected();
		if (ASurvivalPlayerController* PC = Cast<ASurvivalPlayerController>(PlayerCharacter->GetController()))
		{
			PC->CloseInventory();
			PC->GetHUDWidget()->UpdateEquippedItem(Item);
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
