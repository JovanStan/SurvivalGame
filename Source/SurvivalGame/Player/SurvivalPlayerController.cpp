

#include "SurvivalPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Characters/SurvivalCharacter.h"
#include "../UI/HUDWidget.h"
#include "../UI/Inventory/InventoryWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController() && HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void ASurvivalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); IsValid(InputSubsystem))
	{
		for (auto Context : InputMappingContexts)
		{
			InputSubsystem->AddMappingContext(Context, 0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent); IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASurvivalPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASurvivalPlayerController::StopJumping);
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASurvivalPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASurvivalPlayerController::Look);
		
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASurvivalPlayerController::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASurvivalPlayerController::StopSprint);
		
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ASurvivalPlayerController::OpenInventory);
	}
}

void ASurvivalPlayerController::Jump()
{
	if (IsValid(GetCharacter()))
	{
		GetCharacter()->Jump();
		StopSprint();
	}
}

void ASurvivalPlayerController::StopJumping()
{
	if (IsValid(GetCharacter()))
	{
		GetCharacter()->StopJumping();
	}
}

void ASurvivalPlayerController::StartSprint()
{
	if (ASurvivalCharacter* OwnerCharacter = Cast<ASurvivalCharacter>(GetPawn()))
	{
		OwnerCharacter->StartSprint();
	}
}

void ASurvivalPlayerController::StopSprint()
{
	if (ASurvivalCharacter* OwnerCharacter = Cast<ASurvivalCharacter>(GetPawn()))
	{
		OwnerCharacter->StopSprint();
	}
}

void ASurvivalPlayerController::Move(const FInputActionValue& Value)
{
	
	if (IsValid(GetPawn()))
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();

		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		GetPawn()->AddMovementInput(Forward, MovementVector.Y);
		GetPawn()->AddMovementInput(Right, MovementVector.X);
	}
}

void ASurvivalPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void ASurvivalPlayerController::OpenInventory()
{
	if (!IsValid(InventoryWidget))
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		SetShowMouseCursor(true);
		SetInputMode(FInputModeGameAndUI());
		UGameplayStatics::PlaySound2D(this, OpenSound);
	}
	else
	{
		CloseInventory();
	}
}

void ASurvivalPlayerController::CloseInventory()
{
	InventoryWidget->RemoveFromParent();
	InventoryWidget = nullptr;
	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
	UGameplayStatics::PlaySound2D(this, CloseSound);
}
