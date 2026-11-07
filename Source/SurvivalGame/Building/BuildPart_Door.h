
#pragma once

#include "CoreMinimal.h"
#include "BuildPart_Parent.h"
#include "BuildPart_Door.generated.h"

class UBoxComponent;

UCLASS()
class SURVIVALGAME_API ABuildPart_Door : public ABuildPart_Parent
{
	GENERATED_BODY()

public:
	ABuildPart_Door();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> FloorSocket1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> FloorSocket2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> WallSocket1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> WallSocket2;
};
