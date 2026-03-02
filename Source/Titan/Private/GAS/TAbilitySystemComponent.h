// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS/TGameplayAbilityTypes.h"
#include "TAbilitySystemComponent.generated.h"

//////////////////////////////////////////////////////////////////////////
// T Ability System Component

UCLASS()
class UTAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void ApplyInitialEffects();
	void GiveInitialAbilities();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	// Abilities that should be given to the character at the start of the game, such as a combo ability or a dash ability
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TMap<ETAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;

	// Common abilities that should be given to all characters, such as a basic attack or a jump ability
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TMap<ETAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;
};
