// Created by Andrey cb Mikheev


#include "Player/TPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

ATPlayerCharacter::ATPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}

void ATPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	auto OwningPlayerController = GetController<APlayerController>();

	if (OwningPlayerController) {
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if(InputSubsystem){
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}
	}

	if (ViewCamera)
	{
		ViewCamera->SetActive(true);
	}
}

void ATPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}
