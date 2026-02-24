// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "Character/TCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "TPlayerCharacter.generated.h"

//////////////////////////////////////////////////////////////////////////
// T Player Character

UCLASS()
class ATPlayerCharacter : public ATCharacter
{
	GENERATED_BODY()
	
public:
	ATPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	UCameraComponent* ViewCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* GameplayInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Jump;

	void HandleLookInput(const FInputActionValue& Value);
	void HandleMovementInput(const FInputActionValue& Value);

	FVector GetLookFwdDir();
	FVector GetLookRightDir();
	FVector GetMoveFwdDir();
};
