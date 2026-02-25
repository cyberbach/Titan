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
	ATCharacter();
	void ServerSideInit();
	void ClientSideInit();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return TAbilitySystemComponent; }

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UTAbilitySystemComponent* TAbilitySystemComponent;

	UPROPERTY()
	UTAttributeSet* TAttributeSet;
};
