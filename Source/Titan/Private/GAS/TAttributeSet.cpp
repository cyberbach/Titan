// Created by Andrey cb Mikheev

#include "GAS/TAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UTAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UTAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTAttributeSet, Health, OldValue);
}
