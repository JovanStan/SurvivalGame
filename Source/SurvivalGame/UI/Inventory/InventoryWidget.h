
#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


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

	
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UItemsGridWidget> ItemsGrid;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UCanvasPanel> ItemInfoPanel;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> ItemInfoText;
	
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemSlotWidget> ItemSlotClass;
	
private:
	int32 SlotsPerRow = 5;
	
	FTimerHandle TooltipPositionTimerHandle;
	UFUNCTION()
	void TooltipPosition();
};
