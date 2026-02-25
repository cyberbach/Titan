// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//////////////////////////////////////////////////////////////////////////
// T Attribute Set

UCLASS()
class UTAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(UTAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UTAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UTAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UTAttributeSet, MaxMana)

private:
	UPROPERTY()
	FGameplayAttributeData Health;
	UPROPERTY()
	FGameplayAttributeData MaxHealth;
	UPROPERTY()
	FGameplayAttributeData Mana;
	UPROPERTY()
	FGameplayAttributeData MaxMana;
};
