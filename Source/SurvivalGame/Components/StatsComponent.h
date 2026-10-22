
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

class ASurvivalPlayerController;
class ASurvivalCharacter;
class UStatsWidget;
class UProgressBar;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALGAME_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<ASurvivalCharacter> OwnerCharacter;
	UPROPERTY()
	TObjectPtr<ASurvivalPlayerController> OwnerController;
	UStatsComponent();
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bHeal = true;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bRegenStamina = true;
	void AdjustStat(UPARAM(ref) double& Stat, double Amount = 0.05f, double MaxValue = 100.f, bool bDamagePlayer = false, double DamageAmount = 0.05f, UProgressBar* BarWidget = nullptr);
	UStatsWidget* GetStatsWidget() const;

protected:
	virtual void BeginPlay() override;

private:
	void UpdateStatBar(double Stat, double MaxValue, UProgressBar* BarWidget);
	void DamagePlayer(double Amount);
	
	FTimerHandle StatsHandle;
	UFUNCTION()
	void UpdateStats();
	
	// Main Character Stats
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	double Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	double MaxHealth = 100.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	double Hunger;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	double MaxHunger = 100.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	double Thirst;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	double MaxThirst = 100.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	double Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	double MaxStamina = 100.f;
	
public:
	FORCEINLINE double& GetHealth() { return Health; }
	FORCEINLINE double& GetMaxHealth() { return MaxHealth; }
	FORCEINLINE double& GetStamina()  { return Stamina; }
	FORCEINLINE double& GetMaxStamina()  { return MaxStamina; }
	FORCEINLINE double& GetHunger()  { return Hunger; }
	FORCEINLINE double& GetMaxHunger()  { return MaxHunger; }
	FORCEINLINE double& GetThirst()  { return Thirst; }
	FORCEINLINE double& GetMaxThirst()  { return MaxThirst; }
};
