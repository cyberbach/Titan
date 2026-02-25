// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TAbilitySystemComponent.generated.h"

//////////////////////////////////////////////////////////////////////////
// T Ability System Component

UCLASS()
class UTAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void ApplyInitialEffects();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
};
