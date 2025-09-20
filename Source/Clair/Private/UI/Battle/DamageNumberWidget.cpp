// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Battle/DamageNumberWidget.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/RetainerBox.h"


UDamageNumberWidget::UDamageNumberWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{

}

void UDamageNumberWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimationForward(FadeOutAnimation);
}

void UDamageNumberWidget::SetDamageNumber(int32 Damage, bool bIsCritical, bool bIsHeal)
{
	if (DamageText)
	{
		FString DamageString = FString::FromInt(Damage);
		if (bIsHeal)
		{
			DamageText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
		}
	
		DamageText->SetText(FText::FromString(DamageString));
	}

}
