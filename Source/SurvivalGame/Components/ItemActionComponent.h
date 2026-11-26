
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ItemActionComponent.generated.h"


struct FItemData;
struct FConsumableData;
class UBuildingComponent;
class UNiagaraSystem;
class UInventoryWidget;
class ASurvivalPlayerController;
class UInventoryComponent;
class ASurvivalCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALGAME_API UItemActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UItemActionComponent();
	void PrimaryInputAction();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> HarvestMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> TreeHitSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> TreeHitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> RockHitSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> RockHitEffect;
	
	UPROPERTY(EditAnywhere, Category = "Consumables")
	TObjectPtr<UDataTable> ConsumablesDataTable;

	// For Harvest Montage
	void OnHarvestMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload);
	
	
	// References
	UPROPERTY()
	TObjectPtr<ASurvivalCharacter> SurvivalCharacter;
	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;
	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;
	UPROPERTY()
	TObjectPtr<UBuildingComponent> BuildingComponent;
	
	bool bCanAttack;
	const FConsumableData* GetConsumableData(const FItemData& Item) const;
};
