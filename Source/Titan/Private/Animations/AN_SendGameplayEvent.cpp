// Created by Andrey cb Mikheev

#include "Animations/AN_SendGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagsManager.h"

//////////////////////////////////////////////////////////////////////////
// Notify

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}

	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());
	if(!OwnerASC){
		return;
	}

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());
}

//////////////////////////////////////////////////////////////////////////
// Get Notify Name Implementation

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	if(EventTag.IsValid())
	{
		TArray<FName> TagNames;
		UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag,TagNames);
		return TagNames.Last().ToString();
	}

	return "None";
}
