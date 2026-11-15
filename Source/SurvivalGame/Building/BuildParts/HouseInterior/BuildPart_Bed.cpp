
#include "BuildPart_Bed.h"

#include "../../../Characters/SurvivalCharacter.h"
#include "../../../Components/StatsComponent.h"
#include "../../../DayNight/SunRotation.h"
#include "../../../Player/SurvivalPlayerController.h"
#include "../../../UI/StatsWidget.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ABuildPart_Bed::ABuildPart_Bed()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SphereComponent->SetupAttachment(GetRootComponent());
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("Text Render");
	TextRender->SetupAttachment(GetRootComponent());
}

void ABuildPart_Bed::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (TextRender->IsVisible())
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(TextRender->GetComponentLocation(),
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
		TextRender->SetWorldRotation(LookAtRotation);
	}
}

void ABuildPart_Bed::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildPart_Bed::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (ASurvivalCharacter* SurvivalCharacter = Cast<ASurvivalCharacter>(OtherActor))
	{
		TextRender->SetVisibility(true);
	}
}

void ABuildPart_Bed::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if (ASurvivalCharacter* SurvivalCharacter = Cast<ASurvivalCharacter>(OtherActor))
	{
		TextRender->SetVisibility(false);
	}
}

void ABuildPart_Bed::Interact_Implementation()
{
	AActor* SunActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass());
	if (!SunActor) return;

	USunRotation* SunRotation = SunActor->FindComponentByClass<USunRotation>();
	if (!SunRotation) return;

	SunRotation->AddHours(1);
	
	GetWorld()->GetTimerManager().SetTimer(SleepTimer, this, &ABuildPart_Bed::SleepFinished, SleepTime, false);
	if (ASurvivalPlayerController* PlayerController = Cast<ASurvivalPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->DisableInput(PlayerController);
	}
	if (const ASurvivalCharacter* SurvivalCharacter =  Cast<ASurvivalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (UStatsComponent* StatsComponent = SurvivalCharacter->GetStatsComponent())
		{
			StatsComponent->AdjustStat(StatsComponent->GetHealth(), 
				StatsComponent->GetMaxHealth(), StatsComponent->GetMaxHealth(), false, 0, StatsComponent->GetStatsWidget()->HealthBar);
		}
	}
}

void ABuildPart_Bed::SleepFinished()
{
	if (ASurvivalPlayerController* PlayerController = Cast<ASurvivalPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->EnableInput(PlayerController);
	}
	GetWorld()->GetTimerManager().ClearTimer(SleepTimer);
}
