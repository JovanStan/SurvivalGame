
#include "BuildPart_Parent.h"

ABuildPart_Parent::ABuildPart_Parent()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(Root);
}

void ABuildPart_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}
