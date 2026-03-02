// Created by Andrey cb Mikheev


#include "GAS/GA_Combo.h"
#include "GAS/TAbilitySystemStatics.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameplayTagContainer.h"

UGA_Combo::UGA_Combo()
{
	FGameplayTagContainer InitialAbilityTags;
	InitialAbilityTags.AddTag(UTAbilitySystemStatics::GetBasicAttackAbilityTag());
	SetAssetTags(InitialAbilityTags);

	// AbilityTags.AddTag(UTAbilitySystemStatics::GetBasicAttackAbilityTag());
	BlockAbilitiesWithTag.AddTag(UTAbilitySystemStatics::GetBasicAttackAbilityTag());

	UE_LOG(LogTemp, Warning, TEXT("UGA_Combo::UGA_Combo() init tags"));
}

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
	if(!K2_CommitAbility())
	{
		K2_EndAbility();
		//EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		// Play montage and wait for it to end before ending the ability	
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();
	}
}
