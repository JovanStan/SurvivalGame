
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
	
	bool CanCraftItem(FItemData ItemData);
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemData& NewItem);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(const FItemData& NewItem, bool bDecreaseOneOnly);
	
	int GetItemAmount(const FItemData& ItemData);

protected:
	virtual void BeginPlay() override;

private:
	// This is our inventory items (items that we have)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Items")
	TArray<FItemData> Items;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Items")
	TObjectPtr<UDataTable> ItemsDataTable;
	
	UPROPERTY()
	TObjectPtr<ASurvivalPlayerController> SurvivalPlayerController;
	
public:
	FORCEINLINE const TArray<FItemData>& GetItems() const { return Items; }
	FORCEINLINE UDataTable* GetItemsDataTable() const { return ItemsDataTable; }
};
