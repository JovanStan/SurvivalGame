
#include "StatsComponent.h"

#include "../Characters/SurvivalCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "../Player/SurvivalPlayerController.h"
#include "../UI/StatsWidget.h"
#include "../UI/HUDWidget.h"


UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = MaxHealth;
	Hunger = MaxHunger;
	Thirst = MaxThirst;
	Stamina = MaxStamina;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ASurvivalCharacter>(GetOwner());
	OwnerController = Cast<ASurvivalPlayerController>(OwnerCharacter->GetController());
	
	GetWorld()->GetTimerManager().SetTimer(StatsHandle, this, &UStatsComponent::UpdateStats, 0.1f, true);
}

UStatsWidget* UStatsComponent::GetStatsWidget() const
{
	const APawn* OwningPawn = Cast<APawn>(GetOwner());
	const ASurvivalPlayerController* PC = OwningPawn ? Cast<ASurvivalPlayerController>(OwningPawn->GetController()) : nullptr;
	return PC ? PC->GetHUDWidget()->StatsWidget.Get() : nullptr;
}

void UStatsComponent::AdjustStat(double& Stat, double Amount, double MaxValue, bool bDamagePlayer, double DamageAmount, UProgressBar* BarWidget)
{
	Stat = FMath::Clamp(Stat + Amount, 0.f, MaxValue);
	UpdateStatBar(Stat, MaxValue, BarWidget);
	
	if (Stat <= 0 && bDamagePlayer)
	{
		DamagePlayer(DamageAmount);
	}
}

void UStatsComponent::UpdateStatBar(double Stat, double MaxValue, UProgressBar* BarWidget)
{
	if (BarWidget && MaxValue > 0)
	{
		BarWidget->SetPercent(Stat / MaxValue);
	}
}

void UStatsComponent::DamagePlayer(double Amount)
{
	bHeal = false;
	AdjustStat(Health, -Amount, MaxHealth, false, 0.05, GetStatsWidget()->HealthBar);
	if (GetWorld()->GetTimeSeconds() - OwnerCharacter->GetLastDamageSoundTime() >= OwnerCharacter->GetDamageSoundCooldown())
	{
		OwnerCharacter->SetLastDamageSoundTime(GetWorld()->GetTimeSeconds());
		UGameplayStatics::PlaySoundAtLocation(this, OwnerCharacter->GetDamageSound(), OwnerCharacter->GetActorLocation());
	}
	if (Health <= 0)
	{
		if (OwnerCharacter)
		{
			OwnerCharacter->GetMesh()->SetSimulatePhysics(true);
			OwnerController->DisableInput(OwnerController);
			GetWorld()->GetTimerManager().ClearTimer(StatsHandle);
			// Add Death Screen
		}
	}
}

void UStatsComponent::UpdateStats()
{
	// make some kind of table that can be used to change stats values from engine
	if (bHeal)
	{
		AdjustStat(Health, 0.05f, MaxHealth, false, 0.05, GetStatsWidget()->HealthBar);
	}
	if (bRegenStamina)
	{
		AdjustStat(Stamina, 0.2f, MaxStamina, false, 0.05, GetStatsWidget()->StaminaBar);
	}
	
	AdjustStat(Hunger, -0.01f, MaxHunger, true, 0.05, GetStatsWidget()->HungerBar);
	AdjustStat(Thirst, -0.01f, MaxThirst, true, 0.05, GetStatsWidget()->ThirstBar);
	
}


