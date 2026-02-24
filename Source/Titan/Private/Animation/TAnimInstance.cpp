// Created by Andrey cb Mikheev


#include "Animation/TAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

//////////////////////////////////////////////////////////////////////////
// UTAnimInstance

//////////////////////////////////////////////////////////////////////////
// Native Initialize Animation

void UTAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerCharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

//////////////////////////////////////////////////////////////////////////
// Native Update Animation

void UTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (OwnerCharacter)
	{
		Speed = OwnerCharacter->GetVelocity().Length();
		FRotator BodyRot = OwnerCharacter->GetActorRotation();
		FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, PrevBodyRot);
		PrevBodyRot = BodyRot;
		YawSpeed = DeltaRot.Yaw / DeltaSeconds;
		//YawSpeed = FMath::Abs(BodyPrevRot.Yaw - BodyRot.Yaw) / DeltaSeconds;

		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);
	}

	if(OwnerCharacterMovementComponent)
	{
		bIsJumping = OwnerCharacterMovementComponent->IsFalling();
	}
}

//////////////////////////////////////////////////////////////////////////
// Native Thread Safe Update Animation

void UTAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
}
