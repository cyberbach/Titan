// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystemInterface.h"
#include "GAS/TAbilitySystemComponent.h"
#include "GAS/TAttributeSet.h"
#include "TCharacter.generated.h"

//////////////////////////////////////////////////////////////////////////
// T Character

UCLASS()
class ATCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// GAS
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return TAbilitySystemComponent; }
private:
	UTAbilitySystemComponent* TAbilitySystemComponent;
	UTAttributeSet* TAttributeSet;
};
