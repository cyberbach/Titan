// Created by Andrey cb Mikheev

#include "Widgets/ValueGauge.h"
#include "AbilitySystemComponent.h"

//////////////////////////////////////////////////////////////////////////
// Native Pre Construct

void UValueGauge::NativePreConstruct()
{
	Super::NativeConstruct();

	if (ProgressBar)
	{
		ProgressBar->SetFillColorAndOpacity(BarColor);
	}
}

//////////////////////////////////////////////////////////////////////////
// Set And Bound To Gameplay Attribute

void UValueGauge::SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComp, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
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

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UValueGauge::ValueChanged);
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UValueGauge::MaxValueChanged);
}

//////////////////////////////////////////////////////////////////////////
// Set Value

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	CachedValue = NewValue;
	CachedMaxValue = NewMaxValue;

	if (NewMaxValue <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("UValueGauge::SetProgressBarValue: NewMaxValue must be greater than 0. Widget %s"), *GetName());
		return;
	}

	if (ProgressBar)
	{
		ProgressBar->SetPercent(NewValue / NewMaxValue);
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

	ValueText->SetText(
		FText::Format(
			FTextFormat::FromString("{0} / {1}"),
			FText::AsNumber(NewValue, &NumberFormatOptions),
			FText::AsNumber(NewMaxValue, &NumberFormatOptions)
		)
	);
}

//////////////////////////////////////////////////////////////////////////
// Value Changed

void UValueGauge::ValueChanged(const FOnAttributeChangeData& Data)
{
	SetValue(Data.NewValue, CachedMaxValue);
}

//////////////////////////////////////////////////////////////////////////
// Max Value Changed

void UValueGauge::MaxValueChanged(const FOnAttributeChangeData& Data)
{
	SetValue(CachedValue, Data.NewValue);
}
