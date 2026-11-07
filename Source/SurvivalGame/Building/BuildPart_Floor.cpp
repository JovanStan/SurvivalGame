
#include "BuildPart_Floor.h"

#include "Components/BoxComponent.h"


ABuildPart_Floor::ABuildPart_Floor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	FloorSocket1 = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorSocket1"));
	FloorSocket1->SetupAttachment(GetRootComponent());
	FloorSocket2 = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorSocket2"));
	FloorSocket2->SetupAttachment(GetRootComponent());
	FloorSocket3 = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorSocket3"));
	FloorSocket3->SetupAttachment(GetRootComponent());
	FloorSocket4 = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorSocket4"));
	FloorSocket4->SetupAttachment(GetRootComponent());
	
	WallSocket1 = CreateDefaultSubobject<UBoxComponent>(TEXT("WallSocket1"));
	WallSocket1->SetupAttachment(GetRootComponent());
	WallSocket2 = CreateDefaultSubobject<UBoxComponent>(TEXT("WallSocket2"));
	WallSocket2->SetupAttachment(GetRootComponent());
	WallSocket3 = CreateDefaultSubobject<UBoxComponent>(TEXT("WallSocket3"));
	WallSocket3->SetupAttachment(GetRootComponent());
	WallSocket4 = CreateDefaultSubobject<UBoxComponent>(TEXT("WallSocket4"));
	WallSocket4->SetupAttachment(GetRootComponent());
}

void ABuildPart_Floor::BeginPlay()
{
	Super::BeginPlay();
	
}

