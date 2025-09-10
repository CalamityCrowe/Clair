// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BattleHUD.h"
#include "UI/PartyWidget.h"
#include "UI/PartyWidgetSlot.h"
#include "Components/VerticalBox.h"

UBattleHUD::UBattleHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UBattleHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBattleHUD::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBattleHUD::AddPartyToHUD(AUnitBaseCharacter* UnitBase)
{
	UPartyWidgetSlot* NewSlot = CreateWidget<UPartyWidgetSlot>(GetWorld(),PartyWidgetSlotClass);
	if (NewSlot)
	{
		NewSlot->BindToCharacter(UnitBase);
	}
	PartyWidget->PartyBox->AddChildToVerticalBox(NewSlot);
}
