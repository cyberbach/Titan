// Created by Andrey cb Mikheev

#include "Widgets/ValueGuage.h"
#include "AbilitySystemComponent.h"


void UValueGuage::NativePreConstruct()
{
	Super::NativeConstruct();

	if (TProgressBar)
	{
		TProgressBar->SetFillColorAndOpacity(BarColor);
	}
}

void UValueGuage::SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComp, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (!AbilitySystemComp) {
		return;		
	}

	bool bFound;
	float Value = AbilitySystemComp->GetGameplayAttributeValue(Attribute, bFound);
	if(bFound)
	{
		float MaxValue = AbilitySystemComp->GetGameplayAttributeValue(MaxAttribute, bFound);
		if(bFound)
		{
			SetValue(Value, MaxValue);
		}
	}

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UValueGuage::ValueChanged);
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UValueGuage::MaxValueChanged);
}

void UValueGuage::SetValue(float NewValue, float NewMaxValue)
{
	CachedValue = NewValue;
	CachedMaxValue = NewMaxValue;

	if (NewMaxValue <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("UValueGauge::SetProgressBarValue: NewMaxValue must be greater than 0. Widget %s"), *GetName());
		return;
	}

	if (TProgressBar)
	{
		TProgressBar->SetPercent(NewValue / NewMaxValue);
	}

	FNumberFormattingOptions NumberFormatOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	//ValueText->SetText(FText::AsNumber(FMath::RoundToInt(NewValue)), &NumberFormatOptions);
	/*ValueText->SetText(
		FText::Format(
			NSLOCTEXT("ValueGauge", "ValueFormat", "{0} / {1}"), 
			FText::AsNumber(FMath::RoundToInt(NewValue), &NumberFormatOptions), 
			FText::AsNumber(FMath::RoundToInt(NewMaxValue), &NumberFormatOptions)
		)
	);*/

	TValueText->SetText(
		FText::Format(
			FTextFormat::FromString("{0} / {1}"),
			FText::AsNumber(NewValue, &NumberFormatOptions),
			FText::AsNumber(NewMaxValue, &NumberFormatOptions)
		)
	);
}

void UValueGuage::ValueChanged(const FOnAttributeChangeData& Data)
{
	SetValue(Data.NewValue, CachedMaxValue);
}

void UValueGuage::MaxValueChanged(const FOnAttributeChangeData& Data)
{
	SetValue(CachedValue, Data.NewValue);
}
