
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Inventory/Item.h"
#include "InventoryComponent.generated.h"


class ASurvivalPlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	FItem EquippedItem;

protected:
	virtual void BeginPlay() override;
	
	void AddItem(const FItem& NewItem);
	bool RemoveItem(const FItem& NewItem, bool bDecreaseOneOnly);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Items")
	TArray<FItem> Items;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Items")
	TObjectPtr<UDataTable> ItemsDataTable;
	
	UPROPERTY()
	TObjectPtr<ASurvivalPlayerController> SurvivalPlayerController;
	
public:
	FORCEINLINE const TArray<FItem>& GetItems() const { return Items; }
};
