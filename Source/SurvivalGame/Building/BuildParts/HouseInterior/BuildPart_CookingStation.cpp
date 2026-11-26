

#include "BuildPart_CookingStation.h"

#include "NiagaraComponent.h"
#include "../../../Characters/SurvivalCharacter.h"
#include "../../../Components/InventoryComponent.h"
#include "../../../GameplayTags/Survival_Tags.h"
#include "../../../Helper/CommonFunctions.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ABuildPart_CookingStation::ABuildPart_CookingStation()
{
	PrimaryActorTick.bCanEverTick = true;
	
	FireEffect = CreateDefaultSubobject<UNiagaraComponent>("Fire Effect");
	FireEffect->SetupAttachment(GetRootComponent());
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SphereComponent->SetupAttachment(GetRootComponent());
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("Text Render");
	TextRender->SetupAttachment(GetRootComponent());
	
	CookingItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cooking Item Mesh");
	CookingItemMesh->SetupAttachment(GetRootComponent(), "CookingItem");
}

void ABuildPart_CookingStation::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (TextRender->IsVisible())
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(TextRender->GetComponentLocation(),
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
		TextRender->SetWorldRotation(LookAtRotation);
	}
}

void ABuildPart_CookingStation::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (Cast<ASurvivalCharacter>(OtherActor))
	{
		TextRender->SetVisibility(true);
	}
}

void ABuildPart_CookingStation::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if (Cast<ASurvivalCharacter>(OtherActor))
	{
		TextRender->SetVisibility(false);
	}
}

void ABuildPart_CookingStation::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildPart_CookingStation::Interact_Implementation()
{
	IInteract::Interact_Implementation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Cooking Station Interacted");

	ASurvivalCharacter* SurvivalCharacter = Cast<ASurvivalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!SurvivalCharacter) return;
	UInventoryComponent* Inventory = SurvivalCharacter->GetInventoryComponent();
	if (!Inventory) return;
	
	if (bCookingDone)
	{
		Inventory->AddItem(CookedItemData);
		CookingItemMesh->SetStaticMesh(nullptr);
		CookedItemData = FItemData();
		bCookingDone = false;
		return;
	}
	
	if (Inventory->EquippedItem.ItemTag == Survival_Tags::Food::Meat && !bCooking)
	{
		const FItemData& RawItem = Inventory->EquippedItem;
		
		const FItemData* Cooked = RawItem.CookedItem->GetRow<FItemData>(TEXT("CookedItem"));
		if (!Cooked || Cooked->Amount <= 0) return;
		
		CookedItemData = *Cooked;
		CookedItemData.Amount = 1;
		
		CookingItemMesh->SetStaticMesh(RawItem.StaticMesh);
		bCooking = true;
		if (RawItem.CookingTime.IsSet())
		{
			GetWorld()->GetTimerManager().SetTimer(CookingTimer, this, &ABuildPart_CookingStation::CookingFinished, 
						RawItem.CookingTime.GetValue(), false);
		}
		Inventory->RemoveItem(Inventory->EquippedItem, true);
		UCommonFunctions::RemoveEquippedItemAndUpdate(SurvivalCharacter);
	}
}

void ABuildPart_CookingStation::CookingFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Cooking Finished");
	bCooking = false;
	bCookingDone = true;
	CookingItemMesh->SetStaticMesh(CookedItemData.StaticMesh);
}

