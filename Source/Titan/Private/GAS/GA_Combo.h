// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "GAS/TGameplayAbility.h"
#include "GA_Combo.generated.h"

//////////////////////////////////////////////////////////////////////////
// UGA Combo

UCLASS()
class UGA_Combo : public UTGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Combo();

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	static FGameplayTag GetComboChangeEventTag();
	static FGameplayTag GetComboChangeEventEndTag();
	static FGameplayTag GetComboTargetEventTag();

private:
	void SetupWaitComboInputPress();

	UFUNCTION()
	void HandleInputPress(float TimeWaited);

	void TryCommitCombo();

	UPROPERTY(EditAnywhere, Category = "Combo")
	UAnimMontage* ComboMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TMap<FName, TSubclassOf<UGameplayEffect>> DamageEffectsMap;

	TSubclassOf<UGameplayEffect> GetDamageEffectForCurrentCombo() const;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DefaultDamageEffect;

	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void DoDamage(FGameplayEventData Payload);

	FName NextComboSectionName = NAME_None;
};
