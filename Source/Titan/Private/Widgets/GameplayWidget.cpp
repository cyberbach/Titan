// Created by Andrey cb Mikheev

#include "Widgets/GameplayWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/TAttributeSet.h"
#include "Widgets/ValueGauge.h"

//////////////////////////////////////////////////////////////////////////
// Native Construct

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	// OwnerAbilitySystemComponent = GetOwningPlayer() ? GetOwningPlayer()->FindComponentByClass<UAbilitySystemComponent>() : nullptr;

	if(OwnerAbilitySystemComponent)
	{
		if (HealthBar)
		{
			HealthBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComponent, FGameplayAttribute(UTAttributeSet::GetHealthAttribute()), FGameplayAttribute(UTAttributeSet::GetMaxHealthAttribute()));
		}
		if (ManaBar)
		{
			ManaBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComponent, FGameplayAttribute(UTAttributeSet::GetManaAttribute()), FGameplayAttribute(UTAttributeSet::GetMaxManaAttribute()));
		}
	}
}
