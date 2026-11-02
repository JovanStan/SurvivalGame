
#pragma once

#include "CoreMinimal.h"
#include "../../Inventory/ItemData.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "ResourceSlot.generated.h"


class UTextBlock;
class UImage;
class UButton;

UCLASS()
class SURVIVALGAME_API UResourceSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> IconImage;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> AmountText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemData Item;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemAmount;
	
	void SetResource(const FItemData& NewItem, int32 Amount);
	
private:
	FTimerHandle StartDelayTimerHandle;
	UFUNCTION()
	void StartDelay();
};
