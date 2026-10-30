
#include "CommonFunctions.h"

#include "../Characters/SurvivalCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

bool UCommonFunctions::DoSphereTraceForObjects(ASurvivalCharacter* SurvivalCharacter, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, FHitResult& HitResult)
{
	if (!SurvivalCharacter || !SurvivalCharacter->GetController()) return false;
	
	FVector Start;
	FRotator ViewRot;
	SurvivalCharacter->GetController()->GetPlayerViewPoint(Start, ViewRot);

	const FVector End = Start + ViewRot.Vector() * 250.f;
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(SurvivalCharacter);
	
	return UKismetSystemLibrary::SphereTraceSingleForObjects(SurvivalCharacter, Start, 
		End, 20.f, ObjectTypes, 
		false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
}
