

#include "BuildPart_Door.h"

#include "Components/BoxComponent.h"

ABuildPart_Door::ABuildPart_Door()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WallSocket1 = CreateDefaultSubobject<UBoxComponent>(TEXT("WallSocket1"));
	WallSocket1->SetupAttachment(GetRootComponent());
	WallSocket2 = CreateDefaultSubobject<UBoxComponent>(TEXT("WallSocket2"));
	WallSocket2->SetupAttachment(GetRootComponent());
	
	FloorSocket1 = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorSocket1"));
	FloorSocket1->SetupAttachment(GetRootComponent());
	FloorSocket2 = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorSocket2"));
	FloorSocket2->SetupAttachment(GetRootComponent());
}

void ABuildPart_Door::BeginPlay()
{
	Super::BeginPlay();
	
}
