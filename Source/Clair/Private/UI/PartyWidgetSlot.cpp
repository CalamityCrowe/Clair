// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PartyWidgetSlot.h"
#include "Characters/UnitBaseCharacter.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "Characters/Abilities/Tasks/AsyncTaskAttributeChange.h"
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
	if (IsValid(AttributeChangeTask))
	{
		AttributeChangeTask->EndTask();
	}
}

void UPartyWidgetSlot::BindToCharacter(AUnitBaseCharacter* Character)
{
	BoundCharacter = Character;
	if (BoundCharacter)
	{
		CurrentHP = BoundCharacter->GetHealth();

		NameText->SetText(BoundCharacter->GetCharacterName());
		HPNumber->SetText(FText::AsNumber(CurrentHP));
		MaxHPNumber->SetText(FText::AsNumber(BoundCharacter->GetMaxHealth()));
		MPNumber->SetText(FText::AsNumber(BoundCharacter->GetMana()));
		MaxMPNumber->SetText(FText::AsNumber(BoundCharacter->GetMaxMana()));

		TArray<FGameplayAttribute> AttributesToListenFor;
		AttributesToListenFor.Add(UAttributeSetBase::GetHealthAttribute());
		AttributesToListenFor.Add(UAttributeSetBase::GetManaAttribute());
		AttributeChangeTask = UAsyncTaskAttributeChange::ListenForAttributesChange(BoundCharacter->GetAbilitySystemComponent(), AttributesToListenFor);
		if (AttributeChangeTask)
		{
			AttributeChangeTask->OnAttributeChanged.AddDynamic(this, &UPartyWidgetSlot::UpdateHealth);
			AttributeChangeTask->OnAttributeChanged.AddDynamic(this, &UPartyWidgetSlot::UpdateMana);
		}
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

void UPartyWidgetSlot::UpdateHealth(FGameplayAttribute Attribute, float NewValue, float MaxValue)
{
	if (Attribute != UAttributeSetBase::GetHealthAttribute()) return;
	TargetHP = NewValue;

	GetWorld()->GetTimerManager().ClearTimer(StatUpdateTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(StatUpdateTimerHandle, this, &UPartyWidgetSlot::UpdateHealthText, 0.02f, true);

}

void UPartyWidgetSlot::UpdateMana(FGameplayAttribute Attribute, float NewValue, float OldValue)
{
}

void UPartyWidgetSlot::UpdateHealthText()
{
	CurrentHP = FMath::FInterpTo(CurrentHP, TargetHP, GetWorld()->GetDeltaSeconds(), 10);
	HPNumber->SetText(FText::AsNumber(FMath::RoundToInt(CurrentHP)));

	if (FMath::IsNearlyEqual(CurrentHP, TargetHP, 0.01f)) 
	{
		CurrentHP = TargetHP;
		GetWorld()->GetTimerManager().ClearTimer(StatUpdateTimerHandle);
	}
}
