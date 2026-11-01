
#pragma once
#include "CoreMinimal.h"
#include "Recipe.generated.h"

USTRUCT(BlueprintType)
struct FRecipe : public FTableRowBase
{
	GENERATED_BODY()

	FRecipe() = default;
	FRecipe(const FDataTableRowHandle& ItemRow, const int32 InAmount)
	   : Item(ItemRow)
	   , Amount(InAmount)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};