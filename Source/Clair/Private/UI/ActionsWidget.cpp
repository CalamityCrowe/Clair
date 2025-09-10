// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActionsWidget.h"
#include "Characters/UnitBaseCharacter.h"
#include "Components/TextBlock.h"

UActionsWidget::UActionsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


void UActionsWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UActionsWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UActionsWidget::SetBoundCharacter(AUnitBaseCharacter* NewCharacter)
{
	BoundCharacter = NewCharacter;
	if (BoundCharacter)
	{
		NameText->SetText(BoundCharacter->GetCharacterName());
	}
}
