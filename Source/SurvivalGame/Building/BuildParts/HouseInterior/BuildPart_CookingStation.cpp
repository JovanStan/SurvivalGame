

#include "BuildPart_CookingStation.h"

#include "NiagaraComponent.h"
#include "../../../Characters/SurvivalCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ABuildPart_CookingStation::ABuildPart_CookingStation()
{
	PrimaryActorTick.bCanEverTick = true;
	
	FireEffect = CreateDefaultSubobject<UNiagaraComponent>("Fire Effect");
	FireEffect->SetupAttachment(GetRootComponent());
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SphereComponent->SetupAttachment(GetRootComponent());
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("Text Render");
	TextRender->SetupAttachment(GetRootComponent());
}

void ABuildPart_CookingStation::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (TextRender->IsVisible())
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(TextRender->GetComponentLocation(),
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
		TextRender->SetWorldRotation(LookAtRotation);
	}
}

void ABuildPart_CookingStation::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (Cast<ASurvivalCharacter>(OtherActor))
	{
		TextRender->SetVisibility(true);
	}
}

void ABuildPart_CookingStation::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if (Cast<ASurvivalCharacter>(OtherActor))
	{
		TextRender->SetVisibility(false);
	}
}

void ABuildPart_CookingStation::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildPart_CookingStation::Interact_Implementation()
{
	IInteract::Interact_Implementation();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Cooking Station Interacted");
}

