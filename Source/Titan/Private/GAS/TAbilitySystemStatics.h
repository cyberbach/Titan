// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TAbilitySystemStatics.generated.h"

//////////////////////////////////////////////////////////////////////////
// UT Ability System Statics

UCLASS()
class UTAbilitySystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FGameplayTag GetBasicAttackAbilityTag();
	static FGameplayTag GetDeadStatTag();
};
