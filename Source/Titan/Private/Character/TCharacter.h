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
	bool IsLocallyControlledByPlayer() const;
	virtual void PossessedBy(AController* NewController) override;

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

	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	class UWidgetComponent* OverHeadWidgetComponent;

	void ConfigureOverHeadStatusWidget();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float OverHeadWidgetVisibilityUpdateInterval = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float OverHeadWidgetVisibilityDistance = 10000000.0f;

	FTimerHandle OverHeadWidgetVisibilityUpdateTimerHandle;

	void UpdateOverHeadWidgetVisibility();
};
