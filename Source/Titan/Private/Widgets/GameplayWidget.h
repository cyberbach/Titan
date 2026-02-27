// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
public:
	UPROPERTY(meta = (BindWidget))
	class UValueGuage* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UValueGuage* ManaBar;

	UPROPERTY()	
	class UAbilitySystemComponent* OwnerAbilitySystemComponent;
};
