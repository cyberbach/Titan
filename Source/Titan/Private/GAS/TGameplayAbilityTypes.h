// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "TGameplayAbilityTypes.generated.h"

UENUM(BlueprintType)
enum class ETAbilityInputID : uint8
{
	//None = 0 UMETA(Hidden),
	ETAI_None = 0 UMETA(DisplayName = "None"),
	ETAI_BasicAttack UMETA(DisplayName = "Basic Attack"),
	ETAI_AbilityOne UMETA(DisplayName = "Ability One"),
	ETAI_AbilityTwo UMETA(DisplayName = "Ability Two"),
	ETAI_AbilityThree UMETA(DisplayName = "Ability Three"),
	ETAI_AbilityFour UMETA(DisplayName = "Ability Four"),
	ETAI_AbilityFive UMETA(DisplayName = "Ability Five"),
	ETAI_AbilitySix UMETA(DisplayName = "Ability Six"),
	ETAI_Confirm UMETA(DisplayName = "Confirm"),
	ETAI_Cancel UMETA(DisplayName = "Cancel"),
	ETAI_MAX UMETA(Hidden)
};