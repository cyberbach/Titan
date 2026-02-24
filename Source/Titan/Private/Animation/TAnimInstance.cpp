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
		// calculate movement speed
		Speed = OwnerCharacter->GetVelocity().Length();

		// calculate yaw speed
		FRotator BodyRot = OwnerCharacter->GetActorRotation();
		FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, PrevBodyRot);
		PrevBodyRot = BodyRot;
		YawSpeed = DeltaRot.Yaw / DeltaSeconds;
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);

		// calculate aim offset
		FRotator ControlRot = OwnerCharacter->GetBaseAimRotation();
		LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, BodyRot);
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
