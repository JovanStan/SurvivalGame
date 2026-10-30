
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Inventory/ItemData.h"
#include "InventoryComponent.generated.h"


class ASurvivalPlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	FItemData EquippedItem;
	
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemData& NewItem);
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(const FItemData& NewItem, bool bDecreaseOneOnly);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Items")
	TArray<FItemData> Items;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Items")
	TObjectPtr<UDataTable> ItemsDataTable;
	
	UPROPERTY()
	TObjectPtr<ASurvivalPlayerController> SurvivalPlayerController;
	
public:
	FORCEINLINE const TArray<FItemData>& GetItems() const { return Items; }
};
