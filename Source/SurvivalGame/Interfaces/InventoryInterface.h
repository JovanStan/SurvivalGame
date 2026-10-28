
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Inventory/ItemData.h"
#include "InventoryInterface.generated.h"


UINTERFACE()
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};


class SURVIVALGAME_API IInventoryInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void HarvestItem(FItemData Item);
};
