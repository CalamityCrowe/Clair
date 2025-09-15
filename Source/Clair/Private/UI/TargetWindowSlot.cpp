// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TargetWindowSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Characters/UnitBaseCharacter.h"

UTargetWindowSlot::UTargetWindowSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UTargetWindowSlot::NativeConstruct()
{
	Super::NativeConstruct();
	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UTargetWindowSlot::OnSlotClicked);
	}
}

void UTargetWindowSlot::NativeDestruct()
{
	Super::NativeDestruct();
}

void UTargetWindowSlot::SetBoundCharacter(AUnitBaseCharacter* NewCharacter)
{
	BoundCharacter = NewCharacter;
	if (BoundCharacter)
	{
		SlotText->SetText(BoundCharacter->GetCharacterName());
	}
}

void UTargetWindowSlot::OnSlotClicked()
{
	TargetChosen.Broadcast(BoundCharacter);
}
