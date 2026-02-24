// Created by Andrey cb Mikheev


#include "Animation/TAnimInstance.h"

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
}

//////////////////////////////////////////////////////////////////////////
// Native Thread Safe Update Animation

void UTAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
}
