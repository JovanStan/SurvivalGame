
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

struct FItemData;

UINTERFACE()
class UInteract : public UInterface
{
	GENERATED_BODY()
};


class SURVIVALGAME_API IInteract
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void PickupItem(FItemData& Item, bool& bCanPickup);
};
