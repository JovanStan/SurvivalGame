
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalCharacter.generated.h"

struct FItemData;
class UInventoryComponent;
class UStatsComponent;
struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;

UCLASS()
class SURVIVALGAME_API ASurvivalCharacter : public ACharacter
{
	GENERATED_BODY()
	
	
public:
	ASurvivalCharacter();	
	
	void StartSprint();
	void StopSprint();
	void EquipItemMesh(FItemData ItemToEquip);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStatsComponent> StatsComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> EquippedItemMesh;
	
	// Damage Sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> DamageSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float DamageSoundCooldown = 1.f;
	float LastDamageSoundTime = 0.f; 

	FTimerHandle SprintHandle;
	UFUNCTION()
	void DrainStamina();
	
public:
	FORCEINLINE  USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE  UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE USoundBase* GetDamageSound() const { return DamageSound; }
	FORCEINLINE float GetDamageSoundCooldown() const { return DamageSoundCooldown; }
	FORCEINLINE float GetLastDamageSoundTime() const { return LastDamageSoundTime; }
	FORCEINLINE UStatsComponent* GetStatsComponent() const { return StatsComponent; }
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	
	void SetLastDamageSoundTime(float Time) { LastDamageSoundTime = Time; }
};
