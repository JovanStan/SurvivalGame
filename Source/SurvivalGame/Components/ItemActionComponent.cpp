
#include "ItemActionComponent.h"
#include "InventoryComponent.h"
#include "../Characters/SurvivalCharacter.h"
#include "../Helper/CommonFunctions.h"
#include "../Interfaces/FoliageInterface.h"
#include "../Player/SurvivalPlayerController.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

UItemActionComponent::UItemActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	bCanAttack = true;
}

void UItemActionComponent::BeginPlay()
{
	Super::BeginPlay();

	SurvivalCharacter = Cast<ASurvivalCharacter>(GetOwner());
	AnimInstance = SurvivalCharacter->GetMesh()->GetAnimInstance();
	InventoryComponent = SurvivalCharacter->GetInventoryComponent();
	
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UItemActionComponent::OnNotifyBegin);
	}
}

void UItemActionComponent::AttackAndHarvest()
{
	const ASurvivalPlayerController* PC = Cast<ASurvivalPlayerController>(SurvivalCharacter->GetController());
	if (!PC || PC->GetInventoryWidget()) return;
	
	if (InventoryComponent->EquippedItem.Name == "Axe" || InventoryComponent->EquippedItem.Name == "Pickaxe")
	{
		if (bCanAttack && SurvivalCharacter && AttackAndHarvestMontage)
		{
			AnimInstance->Montage_Play(AttackAndHarvestMontage);
			bCanAttack = false;
		
			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(this, &ThisClass::OnAttackAndHarvestMontageEnded);
			SurvivalCharacter->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate, AttackAndHarvestMontage);
		}
	}
}

void UItemActionComponent::OnAttackAndHarvestMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bCanAttack = true;
}

void UItemActionComponent::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	if (!UCommonFunctions::DoSphereTraceForObjects(SurvivalCharacter, ObjectTypes, HitResult)) return;
	
	if (HitResult.bBlockingHit)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, HitResult.ImpactPoint);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, HitResult.ImpactPoint);
		
		if (HitResult.GetComponent()->Implements<UFoliageInterface>())
		{
			IFoliageInterface::Execute_Chop(HitResult.GetComponent(), 10.f, HitResult);
			return;
		}
		
		if (HitResult.GetActor())
		{
			const FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(10.f, DamageEvent, SurvivalCharacter->GetController(), SurvivalCharacter);
		}
	}
}

