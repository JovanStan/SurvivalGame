
#include "BuildingComponent.h"

#include "InventoryComponent.h"
#include "../SurvivalGame.h"
#include "../Building/BuildPart.h"
#include "../Characters/SurvivalCharacter.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	SurvivalCharacter = Cast<ASurvivalCharacter>(GetOwner());
}

void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bInBuildMode || !BuildPreviewMesh || !BuildPartsDataTable) return;
	if (!SurvivalCharacter || !SurvivalCharacter->GetController()) return;

	FVector Start;
	FRotator ViewRot;
	SurvivalCharacter->GetController()->GetPlayerViewPoint(Start, ViewRot);
	const FVector End = Start + ViewRot.Vector() * 500.f;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	const FRotator YawOnly(0.f, ViewRot.Yaw, 0.f);

	// 1) Free placement
	FHitResult GroundHit;
	if (GetWorld()->LineTraceSingleByChannel(GroundHit, Start, End, ECC_Visibility, Params))
	{
		const FVector Offset = YawOnly.Vector() * ForwardOffset + FVector::UpVector * UpOffset;
		BuildPreviewMesh->SetWorldLocationAndRotation(GroundHit.Location + Offset, YawOnly);
	}

	// 2) Snap to a socket
	const FBuildPart* Row = BuildPartsDataTable->FindRow<FBuildPart>(BuildPart.RowName, TEXT("Tick"), false);
	if (!Row) return;

	FHitResult SocketHit;
	bool bSocketHit = GetWorld()->LineTraceSingleByChannel(SocketHit, Start, End, Row->SocketTraceChannel, Params);
	if (bSocketHit)
	{
		const UPrimitiveComponent* SocketComp = SocketHit.GetComponent();
		if (SocketComp)
		{
			BuildPreviewMesh->SetWorldLocationAndRotation(SocketComp->GetComponentLocation(),
				FRotator(0.f, SocketComp->GetComponentRotation().Yaw, 0.f));
		}
	}
}

void UBuildingComponent::BuildMode()
{
	ScreenLog(TEXT("BuildMode called"), FColor::Cyan);
	
	if (!SurvivalCharacter || !BuildPartsDataTable) return;

	const UInventoryComponent* Inv = SurvivalCharacter->GetInventoryComponent();
	if (!Inv) return;

	BuildPart.DataTable = BuildPartsDataTable;
	BuildPart.RowName = FName(*Inv->EquippedItem.Name);

	const FBuildPart* Row = BuildPartsDataTable->FindRow<FBuildPart>(BuildPart.RowName, TEXT("BuildMode"), false);
	if (!Row || !Row->StaticMesh) return; 

	BuildPreviewMesh = Cast<UStaticMeshComponent>(GetOwner()->AddComponentByClass(
		UStaticMeshComponent::StaticClass(), false, FTransform::Identity, false));
	if (!BuildPreviewMesh) return;

	BuildPreviewMesh->SetStaticMesh(Row->StaticMesh);
	BuildPreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (BuildPartMaterial) BuildPreviewMesh->SetMaterial(0, BuildPartMaterial);

	bInBuildMode = true;
}

void UBuildingComponent::StopBuildMode()
{
	bInBuildMode = false;
	if (BuildPreviewMesh)
	{
		BuildPreviewMesh->SetStaticMesh(nullptr);
		BuildPreviewMesh->DestroyComponent();
	}
}

void UBuildingComponent::Build()
{
	const FBuildPart* Row = BuildPartsDataTable->FindRow<FBuildPart>(BuildPart.RowName, TEXT("BuildMode"), false);
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(Row->ActorClass, BuildPreviewMesh->GetComponentLocation(), BuildPreviewMesh->GetComponentRotation(), FActorSpawnParameters());
	
	SurvivalCharacter->GetInventoryComponent()->RemoveItem(SurvivalCharacter->GetInventoryComponent()->EquippedItem, true);
	if (SurvivalCharacter->GetInventoryComponent()->GetItemAmount(SurvivalCharacter->GetInventoryComponent()->EquippedItem) <= 0)
	{
		StopBuildMode();
	}
	
}


