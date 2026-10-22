
#include "BaseItem.h"
#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
}

void ABaseItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if (!bRandomItem)
	{
		if (const FItemData* Row = ItemRow.GetRow<FItemData>(TEXT("ABaseItem::LoadItemData")))
		{
			ItemData = *Row;
			MeshComponent->SetStaticMesh(ItemData.StaticMesh);
		}
	}
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
	// This is for random item spawning
	if (!bRandomItem || PossibleRows.IsEmpty()) return;
	
	if (!ItemRow.DataTable) return;

	const FName RandomRowName = PossibleRows[FMath::RandRange(0, PossibleRows.Num() - 1)];

	if (const FItemData* Row =  ItemRow.DataTable->FindRow<FItemData>(RandomRowName, TEXT("ABaseItem::BeginPlay")))
	{
		ItemData = *Row;
		MeshComponent->SetStaticMesh(ItemData.StaticMesh);
	}
}

