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
		FVector StartLocation = TargetData->HasOrigin() ? TargetData->GetOrigin().GetLocation() : GetAvatarActorFromActorInfo()->GetActorLocation();
		FVector EndLocation = TargetData->HasEndPoint() ? TargetData->GetEndPoint() : GetAvatarActorFromActorInfo()->GetActorLocation();

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore = bIgnoreSelf ? TArray<AActor*>{ GetAvatarActorFromActorInfo() } : TArray<AActor*>();

		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

		TArray<FHitResult> SweepResults;

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
			// display name of hit actor
			//UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());

			if (HitActors.Contains(HitResult.GetActor()))
			{
				// UE_LOG(LogTemp, Log, TEXT("Hit Actor ignored: %s"), *HitResult.GetActor()->GetName());
				continue;
			}

			// UE_LOG(LogTemp, Log, TEXT("Hit Actor not ignored: %s"), *HitResult.GetActor()->GetName());
			HitActors.Add(HitResult.GetActor());
			OutResults.Add(HitResult);
		}
	}

	return OutResults;
}
