#include "SurvivalCharacter.h"

#include "../Components/InventoryComponent.h"
#include "../Components/StatsComponent.h"
#include "../UI/StatsWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASurvivalCharacter::ASurvivalCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), "head");
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	StatsComponent = CreateDefaultSubobject<UStatsComponent>("Stats Component");
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory Component");
	
	EquippedItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Equipped Item Mesh");
	EquippedItemMesh->SetupAttachment(GetMesh(), "hand_r");
}

void ASurvivalCharacter::StartSprint()
{
	if (StatsComponent->GetStamina() <= 0) return;
	
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	StatsComponent->bRegenStamina = false;
	GetWorld()->GetTimerManager().SetTimer(SprintHandle, this, &ASurvivalCharacter::DrainStamina, .01f, true);
}

void ASurvivalCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
	StatsComponent->bRegenStamina = true;
	GetWorld()->GetTimerManager().ClearTimer(SprintHandle);
}

void ASurvivalCharacter::DrainStamina()
{
	StatsComponent->AdjustStat(StatsComponent->GetStamina(), -0.1f, StatsComponent->GetMaxStamina(), false, 0.05f, StatsComponent->GetStatsWidget()->StaminaBar);
	if (StatsComponent->GetStamina() <= 0)
	{
		StopSprint();
	}
}

void ASurvivalCharacter::EquipItemMesh(FItem ItemToEquip)
{
	EquippedItemMesh->SetStaticMesh(ItemToEquip.StaticMesh);
}


