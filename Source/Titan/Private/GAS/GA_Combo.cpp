// Created by Andrey cb Mikheev

#include "GAS/GA_Combo.h"
#include "GAS/TAbilitySystemStatics.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "GameplayTagsManager.h"
#include "AbilitySystemBlueprintLibrary.h"

//////////////////////////////////////////////////////////////////////////
// UGA Combo

UGA_Combo::UGA_Combo()
{
	FGameplayTagContainer InitialAbilityTags;
	InitialAbilityTags.AddTag(UTAbilitySystemStatics::GetBasicAttackAbilityTag());
	SetAssetTags(InitialAbilityTags);

	BlockAbilitiesWithTag.AddTag(UTAbilitySystemStatics::GetBasicAttackAbilityTag());

	//UE_LOG(LogTemp, Warning, TEXT("UGA_Combo::UGA_Combo() init tags"));
}

//////////////////////////////////////////////////////////////////////////
// Activate Ability

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if(!K2_CommitAbility())
	{
		K2_EndAbility();
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

		FGameplayTag EventTag = GetComboChangeEventTag();
		UAbilityTask_WaitGameplayEvent* WaitComboEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EventTag, nullptr, false, false);
		WaitComboEventTask->EventReceived.AddDynamic(this, &UGA_Combo::ComboChangedEventReceived);
		WaitComboEventTask->ReadyForActivation();
	}

	if (K2_HasAuthority()) {
		FGameplayTag EventTag = GetComboTargetEventTag();
		UAbilityTask_WaitGameplayEvent* WaitTargetingEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EventTag, nullptr, false, false);
		WaitTargetingEventTask->EventReceived.AddDynamic(this, &UGA_Combo::DoDamage);
		WaitTargetingEventTask->ReadyForActivation();
	}

	SetupWaitComboInputPress();
}

//////////////////////////////////////////////////////////////////////////
// Get Combo Change Event Tag

FGameplayTag UGA_Combo::GetComboChangeEventTag()
{
	return FGameplayTag::RequestGameplayTag("ability.combo.change");
}

//////////////////////////////////////////////////////////////////////////
// Get Combo Change Event End Tag

FGameplayTag UGA_Combo::GetComboChangeEventEndTag()
{
	return FGameplayTag::RequestGameplayTag("ability.combo.change.end");
}

//////////////////////////////////////////////////////////////////////////
// Get Combo Target Event Tag

FGameplayTag UGA_Combo::GetComboTargetEventTag()
{
	return FGameplayTag::RequestGameplayTag("ability.combo.damage");
}

//////////////////////////////////////////////////////////////////////////
// Setup Wait Combo Input Press

void UGA_Combo::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPressTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPressTask->OnPress.AddDynamic(this, &UGA_Combo::HandleInputPress);
	WaitInputPressTask->ReadyForActivation();
}

//////////////////////////////////////////////////////////////////////////
// Handle Input Press

void UGA_Combo::HandleInputPress(float TimeWaited)
{
	SetupWaitComboInputPress();
	TryCommitCombo();
}

//////////////////////////////////////////////////////////////////////////
// Try Commit Combo

void UGA_Combo::TryCommitCombo()
{
	if(NextComboSectionName == NAME_None)
	{
		return;
	}

	UAnimInstance* OwnerAnimInstance = GetOwnerAnimInstance();
	if(OwnerAnimInstance && OwnerAnimInstance->Montage_IsPlaying(ComboMontage))
	{
		//OwnerAnimInstance->Montage_JumpToSection(NextComboSectionName, ComboMontage);
		FName CurrentSectionName = OwnerAnimInstance->Montage_GetCurrentSection(ComboMontage);
		OwnerAnimInstance->Montage_SetNextSection(CurrentSectionName, NextComboSectionName, ComboMontage);
	}
}

//////////////////////////////////////////////////////////////////////////
// Get Damage Effect For Current Combo

TSubclassOf<UGameplayEffect> UGA_Combo::GetDamageEffectForCurrentCombo() const
{
	UAnimInstance* OwnerAnimInstance = GetOwnerAnimInstance();
	if(OwnerAnimInstance)
	{
		FName CurrentSectionName = OwnerAnimInstance->Montage_GetCurrentSection(ComboMontage);
		const TSubclassOf<UGameplayEffect>* FoundEffectPtr = DamageEffectsMap.Find(CurrentSectionName);

		if(FoundEffectPtr)
		{
			return *FoundEffectPtr;
		}
	}
	return DefaultDamageEffect;
}

//////////////////////////////////////////////////////////////////////////
// Combo Changed Event Received

void UGA_Combo::ComboChangedEventReceived(FGameplayEventData Payload)
{
	FGameplayTag EventTag = Payload.EventTag;

	if(EventTag == GetComboChangeEventEndTag())
	{
		NextComboSectionName = NAME_None;
		UE_LOG(LogTemp, Warning, TEXT("Next combo is cleared"));
	}

	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	NextComboSectionName = TagNames.Last();

	UE_LOG(LogTemp, Warning, TEXT("Next combo section name %s"), *NextComboSectionName.ToString());
}

//////////////////////////////////////////////////////////////////////////
// Do Damage

void UGA_Combo::DoDamage(FGameplayEventData Payload)
{
	TArray<FHitResult> HitResults = GetHitResultFromSweepLocationTargetData(Payload.TargetData, 30.0f, false, true);

	for(const FHitResult& HitResult : HitResults)
	{
		FGameplayAbilitySpecHandle SpecHandle = GetCurrentAbilitySpecHandle();
		int32 AbilityLevel = GetAbilityLevel(SpecHandle, GetCurrentActorInfo());
		TSubclassOf<UGameplayEffect> DamageEffectClass = GetDamageEffectForCurrentCombo();
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, AbilityLevel);

		FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor());
		ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetData);
		
		//UE_LOG(LogTemp, Warning, TEXT("Hit actor %s"), *HitResult.GetActor()->GetName());
	}
}
