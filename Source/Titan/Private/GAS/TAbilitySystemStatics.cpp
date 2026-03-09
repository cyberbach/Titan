// Created by Andrey cb Mikheev

#include "GAS/TAbilitySystemStatics.h"

//////////////////////////////////////////////////////////////////////////
// Get Basic Attack Ability Tag

FGameplayTag UTAbilitySystemStatics::GetBasicAttackAbilityTag()
{
	return FGameplayTag::RequestGameplayTag("ability.basicattack");
}
