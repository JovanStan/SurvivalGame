
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Crafting/Recipe.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FConsumableData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	float HungerRestore = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	float ThirstRestore = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	float HealthRestore = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	float StaminaRestore = 0.f;

	// Optional extras
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	TObjectPtr<USoundBase> UseSound = nullptr;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	
	FItemData() = default;
	FItemData(const FString& InName, int InAmount, UStaticMesh* InStaticMesh, UTexture2D* InIcon, bool bInCanCraft, FGameplayTag InItemTag)
	   : Name(InName)
	   , Amount(InAmount)
	   , StaticMesh(InStaticMesh)
	   , Icon(InIcon)
	   , bCanCraft(bInCanCraft)
	   , ItemTag(InItemTag)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = FString();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanCraft = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRecipe> ResourcesNeeded;
};
