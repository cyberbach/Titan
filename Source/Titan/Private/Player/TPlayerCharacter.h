// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "Character/TCharacter.h"
#include "TPlayerCharacter.generated.h"

/**
 * 
 */
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
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class UCameraComponent* ViewCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* GameplayInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Jump;
};
