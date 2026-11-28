
#pragma once

#include "CoreMinimal.h"
#include "../BuildPart_Parent.h"
#include "../../../Interfaces/Interact.h"
#include "BuildPart_Bed.generated.h"

class UTextRenderComponent;
class USphereComponent;

UCLASS()
class SURVIVALGAME_API ABuildPart_Bed : public ABuildPart_Parent, public IInteract
{
	GENERATED_BODY()

public:
	ABuildPart_Bed();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	virtual void Interact_Implementation() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SleepAnimation();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UTextRenderComponent> TextRender;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float SleepTime = 4.f;
	
	FTimerHandle SleepTimer;
	UFUNCTION()
	void SleepFinished();
	
};
