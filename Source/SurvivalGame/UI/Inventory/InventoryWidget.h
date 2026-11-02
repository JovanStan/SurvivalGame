
#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemData.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


class UResourceSlot;
class UCraftingSlot;
class UInventoryComponent;
struct FRecipe;
class UButton;
class UCraftingWidget;
class UCanvasPanel;
struct FItemData;
class UTextBlock;
class UItemSlotWidget;
class UItemsGridWidget;

UCLASS()
class SURVIVALGAME_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetSelected();
	
	void ShowItemInfo(FItemData ItemHovered, bool bShowAmount);
	void HideItemInfo();
	void HandleSlotHovered(const FItemData& ItemHovered);
	
	void DisplayCraftingResources(TArray<FRecipe> Resources, FItemData ItemToCraft);
	UFUNCTION()
	void CraftButtonPressed();

	
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UItemsGridWidget> ItemsGrid;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UItemsGridWidget> CraftItemsGrid;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UCraftingWidget> CraftingWidget;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> RecipeText;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UButton> CraftButton;
	
	
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UCanvasPanel> ItemInfoPanel;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> ItemInfoText;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemSlotWidget> ItemSlotClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UResourceSlot> ResourceSlotClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCraftingSlot> CraftingSlotClass;
	
	FItemData ItemToCraftSelected;
	
private:
	int32 SlotsPerRow = 5;
	
	FTimerHandle TooltipPositionTimerHandle;
	UFUNCTION()
	void TooltipPosition();
	
	UPROPERTY()
	TObjectPtr<UInventoryComponent> Inventory;
	UPROPERTY()
	TArray<FItemData> CraftableItemsList;
	
	void UpdateInventory();
};
