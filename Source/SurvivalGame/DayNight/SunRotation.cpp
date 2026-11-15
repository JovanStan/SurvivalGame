
#include "SunRotation.h"

USunRotation::USunRotation()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USunRotation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Rotate Sun and basically make a day / night cycle
	SunRotation = DaySpeed * DeltaTime;
	GetOwner()->AddActorLocalRotation(FRotator(SunRotation, 0, 0));
}

// This will be used to advance time when we sleep
void USunRotation::AddHours(float Hours)
{
	GetOwner()->AddActorLocalRotation(FRotator(Hours * 15.f, 0.f, 0.f));
}

