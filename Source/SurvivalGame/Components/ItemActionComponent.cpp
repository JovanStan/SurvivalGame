
#include "ItemActionComponent.h"

#include "../Characters/SurvivalCharacter.h"
#include "../Helper/CommonFunctions.h"
#include "../Player/SurvivalPlayerController.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

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
	SurvivalPlayerController = Cast<ASurvivalPlayerController>(SurvivalCharacter->GetController());
	InventoryWidget = SurvivalPlayerController->GetInventoryWidget();
	
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UItemActionComponent::OnNotifyBegin);
	}
}

void UItemActionComponent::AttackAndHarvest()
{
	if (InventoryWidget) return;
	
	if (bCanAttack && SurvivalCharacter && AttackAndHarvestMontage)
	{
		AnimInstance->Montage_Play(AttackAndHarvestMontage);
		bCanAttack = false;
		
		
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ThisClass::OnAttackAndHarvestMontageEnded);
		SurvivalCharacter->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate, AttackAndHarvestMontage);
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
		const FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(10.f, DamageEvent, SurvivalPlayerController, SurvivalCharacter);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, HitResult.ImpactPoint);
	}
}

