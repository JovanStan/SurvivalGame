
#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "../Interfaces/Interact.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class USphereComponent;
struct FDataTableRowHandle;

UCLASS()
class SURVIVALGAME_API ABaseItem : public AActor, public IInteract
{
	GENERATED_BODY()

public:
	ABaseItem();
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void PickupItem_Implementation(FItemData& Item, bool& bCanPickup) override;
	
protected:
	virtual void BeginPlay() override; 

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Item")
	FItemData ItemData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Item")
	FDataTableRowHandle ItemRow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Item")
	bool bRandomItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TArray<FName> PossibleRows = { TEXT("Wood"), TEXT("Stone"), TEXT("Banana") };
};
