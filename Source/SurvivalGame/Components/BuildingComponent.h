
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"


class ASurvivalCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALGAME_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuildingComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category = "Building")
	float ForwardOffset = 50.f;
	UPROPERTY(EditAnywhere, Category = "Building")
	float UpOffset = 20.f;
	
	void Build();
	void BuildMode();
	void StopBuildMode();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> BuildPartsDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMaterial> BuildPartMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	FDataTableRowHandle BuildPart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bInBuildMode;
	
	UPROPERTY()
	TObjectPtr<ASurvivalCharacter> SurvivalCharacter;
	UPROPERTY()
	UStaticMeshComponent* BuildPreviewMesh;

	
public:
	FORCEINLINE bool GetInBuildMode() const { return bInBuildMode; }
};
