
#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "../../Inventory/ItemData.h"
#include "ItemSlotWidget.generated.h"


class UTextBlock;
class UImage;
class UButton;

DECLARE_DELEGATE_OneParam(FOnItemSlotHovered, const FItemData&);
DECLARE_DELEGATE(FOnItemSlotUnhovered);

UCLASS()
class SURVIVALGAME_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void SetSelected();
	
	FOnItemSlotHovered OnSlotHovered;
	FOnItemSlotUnhovered OnSlotUnhovered;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ItemButton;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> IconImage;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> AmountText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemData Item;
	
private:
	FTimerHandle StartDelayTimerHandle;
	UFUNCTION()
	void StartDelay();
	
	UFUNCTION()
	void OnItemButtonPressed();
	UFUNCTION()
	void OnItemButtonHovered();
	UFUNCTION()
	void OnItemButtonUnhovered();
	
};
