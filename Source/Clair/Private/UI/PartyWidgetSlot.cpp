// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PartyWidgetSlot.h"
#include "Characters/UnitBaseCharacter.h"
#include "Components/TextBlock.h"

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
