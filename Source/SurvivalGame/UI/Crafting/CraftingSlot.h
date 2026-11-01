
#pragma once

#include "CoreMinimal.h"
#include "../../Inventory/ItemData.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "CraftingSlot.generated.h"

class UInventoryComponent;
class UImage;
class UButton;


UCLASS()
class SURVIVALGAME_API UCraftingSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void SetSelected(FLinearColor LinearColor);
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ItemButton;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> IconImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemData Item;

private:
	FTimerHandle StartDelayTimerHandle;
	UFUNCTION()
	void StartDelay();
	
	UPROPERTY()
	TObjectPtr<UInventoryComponent> Inventory;
	
	UFUNCTION()
	void ItemButtonPressed();
};
