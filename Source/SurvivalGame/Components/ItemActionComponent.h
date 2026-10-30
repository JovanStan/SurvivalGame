
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemActionComponent.generated.h"


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
	void AttackAndHarvest();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> AttackAndHarvestMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> HitSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> HitEffect;
	
	void OnAttackAndHarvestMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload);
	
	UPROPERTY()
	TObjectPtr<ASurvivalCharacter> SurvivalCharacter;
	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;
	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
	
	bool bCanAttack;
};
