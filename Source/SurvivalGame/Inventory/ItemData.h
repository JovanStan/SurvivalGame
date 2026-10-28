
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	
	FItemData() = default;
	FItemData(const FString& InName, int InAmount, UStaticMesh* InStaticMesh, UTexture2D* InIcon, bool bInCanCraft)
	   : Name(InName)
	   , Amount(InAmount)
	   , StaticMesh(InStaticMesh)
	   , Icon(InIcon)
	   , bCanCraft(bInCanCraft)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name = FString();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Amount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanCraft = false;
};
