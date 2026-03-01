// Created by Andrey cb Mikheev

#include "Widgets/OverHeadStatsGauge.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/TAttributeSet.h"
#include "Widgets/ValueGauge.h"

//////////////////////////////////////////////////////////////////////////
// Configure With ASC

void UOverHeadStatsGauge::ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComp)
{
	if (AbilitySystemComp)
	{
		if (HealthBar)
		{
			HealthBar->SetAndBoundToGameplayAttribute(AbilitySystemComp, FGameplayAttribute(UTAttributeSet::GetHealthAttribute()), FGameplayAttribute(UTAttributeSet::GetMaxHealthAttribute()));
		}
		if (ManaBar)
		{
			ManaBar->SetAndBoundToGameplayAttribute(AbilitySystemComp, FGameplayAttribute(UTAttributeSet::GetManaAttribute()), FGameplayAttribute(UTAttributeSet::GetMaxManaAttribute()));
		}
	}
}
