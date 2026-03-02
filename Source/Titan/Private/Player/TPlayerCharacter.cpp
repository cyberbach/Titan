// Created by Andrey cb Mikheev

#include "Player/TPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"

//////////////////////////////////////////////////////////////////////////
// ATPlayerCharacter

ATPlayerCharacter::ATPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

//////////////////////////////////////////////////////////////////////////
// Pawn Client Restart

void ATPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	auto OwningPlayerController = GetController<APlayerController>();

	if (OwningPlayerController) {
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem) {
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}
	}

	if (ViewCamera)
	{
		ViewCamera->SetActive(true);
	}
}

//////////////////////////////////////////////////////////////////////////
// Setup Player Input Component

void ATPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::HandleLookInput);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::HandleMovementInput);

		for(const auto& Pair : GameplayAbilityInputActions)
		{
			if(Pair.Value)
			{
				EnhancedInputComponent->BindAction(Pair.Value, ETriggerEvent::Triggered, this, &ATPlayerCharacter::HandleAbilityInput, Pair.Key);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Handle Look Input

void ATPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

//////////////////////////////////////////////////////////////////////////
// Handle Movement Input

void ATPlayerCharacter::HandleMovementInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	InputValue.Normalize();

	AddMovementInput(GetMoveFwdDir() * InputValue.Y + GetLookRightDir() * InputValue.X);
}

void ATPlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue, ETAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();
	if(bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed((int32)InputID);
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased((int32)InputID);
	}
}

//////////////////////////////////////////////////////////////////////////
// Get Look Fwd Dir

FVector ATPlayerCharacter::GetLookFwdDir()
{
	return ViewCamera->GetForwardVector();
}

//////////////////////////////////////////////////////////////////////////
// Get Look Right Dir

FVector ATPlayerCharacter::GetLookRightDir()
{
	return ViewCamera->GetRightVector();
}

//////////////////////////////////////////////////////////////////////////
// Get Move Fwd Dir

FVector ATPlayerCharacter::GetMoveFwdDir()
{
	return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}
