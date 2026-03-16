// Created by Andrey cb Mikheev

#include "GAS/TAbilitySystemComponent.h"
#include "GAS/TAttributeSet.h"

//////////////////////////////////////////////////////////////////////////
// ctor UT Ability System Component

UTAbilitySystemComponent::UTAbilitySystemComponent()
{
	GetGameplayAttributeValueChangeDelegate(UTAttributeSet::GetHealthAttribute()).AddUObject(this, &UTAbilitySystemComponent::HealthUpdated);
}

//////////////////////////////////////////////////////////////////////////
// Apply Initial Effects

void UTAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		if (EffectClass)
		{
			FGameplayEffectContextHandle EffectInstigatorContext = MakeEffectContext();
			EffectInstigatorContext.AddSourceObject(this);

			FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(EffectClass, 1, EffectInstigatorContext);
			if (SpecHandle.IsValid())
			{
				ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Give Initial Abilities

void UTAbilitySystemComponent::GiveInitialAbilities()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	for (const TPair<ETAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, (int32)AbilityPair.Key, nullptr));
	}

	for (const TPair<ETAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : BasicAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, (int32)AbilityPair.Key, nullptr));
	}
}

//////////////////////////////////////////////////////////////////////////
// Health Updated (delegate)

void UTAbilitySystemComponent::HealthUpdated(const FOnAttributeChangeData& Data)
{
	if(!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	if(Data.NewValue <= 0 && DeathEffect)
	{
		FGameplayEffectContextHandle EffectInstigatorContext = MakeEffectContext();
		EffectInstigatorContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(DeathEffect, 1, EffectInstigatorContext);
		if (SpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

