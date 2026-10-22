
#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "StatsWidget.generated.h"


class UProgressBar;

UCLASS()
class SURVIVALGAME_API UStatsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> StaminaBar;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HungerBar;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> ThirstBar;
};
