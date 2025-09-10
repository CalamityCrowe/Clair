// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PartyWidgetSlot.h"
#include "Characters/UnitBaseCharacter.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/CombatComponent.h"	

#include "Kismet/KismetMathLibrary.h"

UPartyWidgetSlot::UPartyWidgetSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UPartyWidgetSlot::NativeConstruct()
{
	Super::NativeConstruct();
	

}

void UPartyWidgetSlot::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPartyWidgetSlot::BindToCharacter(AUnitBaseCharacter* Character)
{
	BoundCharacter = Character;
	if (BoundCharacter)
	{
		NameText->SetText(BoundCharacter->GetCharacterName());
		HPNumber->SetText(FText::AsNumber(BoundCharacter->GetHealth()));
		MaxHPNumber->SetText(FText::AsNumber(BoundCharacter->GetMaxHealth()));
		MPNumber->SetText(FText::AsNumber(BoundCharacter->GetMana()));
		MaxMPNumber->SetText(FText::AsNumber(BoundCharacter->GetMaxMana()));

	}

}

float UPartyWidgetSlot::UpdateProgressBar()
{
	if (BoundCharacter)
	{
		float TimeRemaing = GetWorld()->GetTimerManager().GetTimerRemaining(BoundCharacter->GetCombatComponent()->GetActionTimer());
		float TimeElapsed = GetWorld()->GetTimerManager().GetTimerElapsed(BoundCharacter->GetCombatComponent()->GetActionTimer());
		float TotalTime = TimeRemaing + TimeElapsed;
		if (TimeRemaing <= 0.0f)
		{
			return 1.0f;
		}
		float Percent = UKismetMathLibrary::NormalizeToRange(TimeElapsed, 0.0f, TotalTime);
		return Percent;
	}
	return 0.0f;
}
