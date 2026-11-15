
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildPart_Parent.generated.h"

UCLASS()
class SURVIVALGAME_API ABuildPart_Parent : public AActor
{
	GENERATED_BODY()

public:
	ABuildPart_Parent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
};
