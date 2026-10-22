
#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "ItemsGridWidget.generated.h"


class UUniformGridPanel;
class UBorder;

UCLASS()
class SURVIVALGAME_API UItemsGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder> Border;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	TObjectPtr<UUniformGridPanel> GridPanel;
};
