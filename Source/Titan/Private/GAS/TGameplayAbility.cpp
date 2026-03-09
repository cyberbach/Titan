// Created by Andrey cb Mikheev

#include "GAS/TGameplayAbility.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

//////////////////////////////////////////////////////////////////////////
// Get Owner Anim Instance

UAnimInstance* UTGameplayAbility::GetOwnerAnimInstance() const
{
	USkeletalMeshComponent* OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo();
	if (OwnerSkeletalMeshComponent) {
		return OwnerSkeletalMeshComponent->GetAnimInstance();
	}

	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Get Hit Result From Sweep Location Target Data

TArray<FHitResult> UTGameplayAbility::GetHitResultFromSweepLocationTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, float SphereSweepRadius, bool bDrawDebug, bool bIgnoreSelf) const
{
	TArray<FHitResult> OutResults;
	TSet<AActor*> HitActors;

	for (const TSharedPtr<FGameplayAbilityTargetData>& TargetData : TargetDataHandle.Data)
	{
		TArray<FHitResult> SweepResults;

		FVector StartLocation = TargetData->HasOrigin() ? TargetData->GetOrigin().GetLocation() : GetAvatarActorFromActorInfo()->GetActorLocation();
		FVector EndLocation = TargetData->HasEndPoint() ? TargetData->GetEndPoint() : GetAvatarActorFromActorInfo()->GetActorLocation();

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore = bIgnoreSelf ? TArray<AActor*>{ GetAvatarActorFromActorInfo() } : TArray<AActor*>();

		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

		UKismetSystemLibrary::SphereTraceMultiForObjects(
			this,
			StartLocation,
			EndLocation,
			SphereSweepRadius,
			ObjectTypes,
			false,
			ActorsToIgnore,
			DrawDebugTrace,
			SweepResults,
			true
		);

		for(const FHitResult& HitResult : SweepResults)
		{
			if (HitActors.Contains(HitResult.GetActor()))
			{
				continue;
			}
			HitActors.Add(HitResult.GetActor());
			OutResults.Add(HitResult);
		}
	}

	return OutResults;
}
