// Created by Andrey cb Mikheev

#include "Player/TPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	}
}

//////////////////////////////////////////////////////////////////////////
// Handle Look Input

void ATPlayerCharacter::HandleLookInput(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

//////////////////////////////////////////////////////////////////////////
// Handle Movement Input

void ATPlayerCharacter::HandleMovementInput(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();
	InputValue.Normalize();

	AddMovementInput(GetMoveFwdDir() * InputValue.Y + GetLookRightDir() * InputValue.X);
}

FVector ATPlayerCharacter::GetLookFwdDir()
{
	return ViewCamera->GetForwardVector();
}

FVector ATPlayerCharacter::GetLookRightDir()
{
	return ViewCamera->GetRightVector();
}

FVector ATPlayerCharacter::GetMoveFwdDir()
{
	return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}
