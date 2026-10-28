
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonFunctions.generated.h"


class ASurvivalCharacter;

UCLASS()
class SURVIVALGAME_API UCommonFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static bool DoSphereTraceForObjects(ASurvivalCharacter* SurvivalCharacter, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, FHitResult& HitResult);
};
