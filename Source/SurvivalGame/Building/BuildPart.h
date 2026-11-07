
#pragma once
#include "CoreMinimal.h"
#include "BuildPart.generated.h"

USTRUCT(BlueprintType)
struct FBuildPart : public FTableRowBase
{
	GENERATED_BODY()
	
	FBuildPart() = default;
	FBuildPart(FString Name, TSubclassOf<AActor> ActorClass, UStaticMesh* StaticMesh, ETraceTypeQuery SocketTraceChannel)
	   : Name(Name)
	   , ActorClass(ActorClass)
	   , StaticMesh(StaticMesh)
	   , SocketTraceChannel(SocketTraceChannel)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> SocketTraceChannel;
};

