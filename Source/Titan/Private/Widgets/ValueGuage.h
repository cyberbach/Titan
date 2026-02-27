// Created by Andrey cb Mikheev

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "ValueGuage.generated.h"

/**
 * 
 */
UCLASS()
class UValueGuage : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComp,const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);
	void SetValue(float NewValue, float NewMaxValue);

private:
	void ValueChanged(const FOnAttributeChangeData& Data);
	void MaxValueChanged(const FOnAttributeChangeData& Data);

	float CachedValue;
	float CachedMaxValue;

	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* TProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* TValueText;
};
