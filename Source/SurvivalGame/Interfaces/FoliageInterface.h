
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FoliageInterface.generated.h"

UINTERFACE(BlueprintType)
class UFoliageInterface : public UInterface
{
	GENERATED_BODY()
};


class SURVIVALGAME_API IFoliageInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Chop(float Damage, FHitResult HitResult);
};
