
#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "CraftingWidget.generated.h"


class UVerticalBox;

UCLASS()
class SURVIVALGAME_API UCraftingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox;
};
