
#include "Resource.h"

#include "ItemData.h"
#include "../Interfaces/InventoryInterface.h"

AResource::AResource()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
}

float AResource::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float Result = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (DamageCauser && DamageCauser->Implements<UInventoryInterface>() && !Items.IsEmpty())
	{
		const FDataTableRowHandle& Handle = Items[FMath::RandRange(0, Items.Num() - 1)];
		
		if (const FItemData* Row = Handle.GetRow<FItemData>(TEXT("AResource::TakeDamage")))
		{
			FItemData Item = *Row;
			Item.Amount = FMath::RandRange(2, 5);   
			IInventoryInterface::Execute_HarvestItem(DamageCauser, Item);
		}
	}
	return Result;
}

void AResource::BeginPlay()
{
	Super::BeginPlay();
}

