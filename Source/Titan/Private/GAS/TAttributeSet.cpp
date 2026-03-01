// Created by Andrey cb Mikheev

#include "GAS/TAttributeSet.h"
#include "Net/UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// Get Lifetime Replicated Props

void UTAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

//////////////////////////////////////////////////////////////////////////
// On Rep Health

void UTAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTAttributeSet, Health, OldValue);
}

//////////////////////////////////////////////////////////////////////////
// On Rep Max Health

void UTAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTAttributeSet, MaxHealth, OldValue);
}

//////////////////////////////////////////////////////////////////////////
// On Rep Mana

void UTAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTAttributeSet, Mana, OldValue);
}

//////////////////////////////////////////////////////////////////////////
// On Rep Max Mana

void UTAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTAttributeSet, MaxMana, OldValue);
}