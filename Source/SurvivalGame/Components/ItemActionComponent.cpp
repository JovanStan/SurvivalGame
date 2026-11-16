
#include "ItemActionComponent.h"

#include "BuildingComponent.h"
#include "InventoryComponent.h"
#include "../Characters/SurvivalCharacter.h"
#include "../Helper/CommonFunctions.h"
#include "../Interfaces/FoliageInterface.h"
#include "../Player/SurvivalPlayerController.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "StatsComponent.h"
#include "GameplayTags/Survival_Tags.h"

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
	BuildingComponent = SurvivalCharacter->GetBuildingComponent();
	
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UItemActionComponent::OnNotifyBegin);
	}
}

void UItemActionComponent::PrimaryInputAction()
{
	const ASurvivalPlayerController* PC = Cast<ASurvivalPlayerController>(SurvivalCharacter->GetController());
	if (!PC || PC->GetInventoryWidget()) return;
	
	if (InventoryComponent->EquippedItem.ItemTag == Survival_Tags::Tools::Axe || InventoryComponent->EquippedItem.ItemTag == Survival_Tags::Tools::Pickaxe)
	{
		if (bCanAttack && SurvivalCharacter && HarvestMontage)
		{
			AnimInstance->Montage_Play(HarvestMontage);
			bCanAttack = false;
		
			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(this, &ThisClass::OnHarvestMontageEnded);
			SurvivalCharacter->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate, HarvestMontage);
		}
	}
	else if (EatingTags.HasTagExact(InventoryComponent->EquippedItem.ItemTag) 
		&& SurvivalCharacter->GetStatsComponent()->GetHunger() < SurvivalCharacter->GetStatsComponent()->GetMaxHunger())
	{
		SurvivalCharacter->GetStatsComponent()->Eat();
		RemoveEquippedItemAndUpdate();
	}
	else if (DrinkingTags.HasTagExact(InventoryComponent->EquippedItem.ItemTag))
	{
		SurvivalCharacter->GetStatsComponent()->Drink();
		RemoveEquippedItemAndUpdate();
	}
}

void UItemActionComponent::RemoveEquippedItemAndUpdate()
{
	SurvivalCharacter->GetInventoryComponent()->RemoveItem(InventoryComponent->EquippedItem, true);
	if (SurvivalCharacter->GetInventoryComponent()->GetItemAmount(SurvivalCharacter->GetInventoryComponent()->EquippedItem) <= 0)
	{
		SurvivalCharacter->GetInventoryComponent()->EquippedItem = FItemData();
		SurvivalCharacter->EquipItemMesh(FItemData());
	}
}


void UItemActionComponent::OnHarvestMontageEnded(UAnimMontage* Montage, bool bInterrupted)
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
		// This is for chopping a tree, because trees are Foliage Instanced Static Meshes
		if (HitResult.GetComponent()->Implements<UFoliageInterface>() && InventoryComponent->EquippedItem.ItemTag == Survival_Tags::Tools::Axe)
		{
			IFoliageInterface::Execute_Chop(HitResult.GetComponent(), 10.f, HitResult);
			if (TreeHitSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), TreeHitSound, HitResult.ImpactPoint);
			if (TreeHitEffect) UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TreeHitEffect, HitResult.ImpactPoint);
			return;
		}
		
		// This is for mining rock, because rocks are Resource items (can be done the same for a tree, but it's much simpler with foliage static meshes)
		if (HitResult.GetActor() && InventoryComponent->EquippedItem.ItemTag == Survival_Tags::Tools::Pickaxe)
		{
			const FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(10.f, DamageEvent, SurvivalCharacter->GetController(), SurvivalCharacter);
			if (RockHitSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), RockHitSound, HitResult.ImpactPoint);
			if (RockHitEffect) UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), RockHitEffect, HitResult.ImpactPoint);
		}
	}
}

