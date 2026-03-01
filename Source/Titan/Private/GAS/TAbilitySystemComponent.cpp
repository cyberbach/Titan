// Created by Andrey cb Mikheev

#include "GAS/TAbilitySystemComponent.h"

//////////////////////////////////////////////////////////////////////////
// Apply Initial Effects

void UTAbilitySystemComponent::ApplyInitialEffects()
{
	if(!GetOwner() || !GetOwner()->HasAuthority())
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
