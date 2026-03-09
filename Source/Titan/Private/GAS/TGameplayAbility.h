// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TGameplayAbility.generated.h"

//////////////////////////////////////////////////////////////////////////
// UT Gameplay Ability

UCLASS()
class UTGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

protected:
	class UAnimInstance* GetOwnerAnimInstance() const;
	TArray<FHitResult> GetHitResultFromSweepLocationTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, float SphereSweepRadius = 30.0f, bool bDrawDebug = false, bool bIgnoreSelf = true) const;
};
