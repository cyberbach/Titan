// Created by Andrey cb Mikheev

#include "GAS/TAbilitySystemStatics.h"

FGameplayTag UTAbilitySystemStatics::GetBasicAttackAbilityTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.BasicAttack");
}
