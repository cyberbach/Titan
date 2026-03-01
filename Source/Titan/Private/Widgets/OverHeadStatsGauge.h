// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <AbilitySystemComponent.h>
#include "OverHeadStatsGauge.generated.h"

//////////////////////////////////////////////////////////////////////////
// U Over Head Stats Gauge

UCLASS()
class UOverHeadStatsGauge : public UUserWidget
{
	GENERATED_BODY()

public:
	void ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComp);

private:
	UPROPERTY(meta = (BindWidget))
	class UValueGauge* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UValueGauge* ManaBar;
};
