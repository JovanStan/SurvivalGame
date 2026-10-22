
#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"


struct FItemData;
class UTextBlock;
class UImage;
class UStatsWidget;

UCLASS()
class SURVIVALGAME_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UStatsWidget> StatsWidget;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UImage> EquippedItemIcon;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> EquippedItemText;
	
	void UpdateEquippedItem(FItemData Item);
	
	UFUNCTION(BlueprintImplementableEvent)
	void AddItemNotifications(const FString& ItemName, UTexture2D* ItemIcon, int32 ItemAmount);
};
