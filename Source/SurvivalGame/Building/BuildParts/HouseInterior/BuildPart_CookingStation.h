
#pragma once

#include "CoreMinimal.h"
#include "../BuildPart_Parent.h"
#include "../../../Interfaces/Interact.h"
#include "../../../Inventory/ItemData.h"
#include "BuildPart_CookingStation.generated.h"

class UNiagaraComponent;
class UTextRenderComponent;
class USphereComponent;

UCLASS()
class SURVIVALGAME_API ABuildPart_CookingStation : public ABuildPart_Parent, public IInteract
{
	GENERATED_BODY()

public:
	ABuildPart_CookingStation();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void Interact_Implementation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookingStation", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> FireEffect;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UTextRenderComponent> TextRender;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> CookingItemMesh;
	
	FTimerHandle CookingTimer;
	UFUNCTION()
	void CookingFinished();
	
	bool bCooking = false;
	bool bCookingDone = false;
	
	FItemData CookedItemData;
};
