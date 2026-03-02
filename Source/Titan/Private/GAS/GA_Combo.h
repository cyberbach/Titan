// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "GAS/TGameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class UGA_Combo : public UTGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Combo();

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditAnywhere, Category = "Combo")
	UAnimMontage* ComboMontage;
};
