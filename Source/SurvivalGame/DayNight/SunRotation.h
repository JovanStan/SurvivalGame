
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SunRotation.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALGAME_API USunRotation : public USceneComponent
{
	GENERATED_BODY()

public:
	USunRotation();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddHours(float Hours);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float DaySpeed = 5.f;
	
	float SunRotation;
};
