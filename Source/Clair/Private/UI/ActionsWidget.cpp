// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActionsWidget.h"
#include "Characters/UnitBaseCharacter.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UI/ActionButton.h"

UActionsWidget::UActionsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


void UActionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(AttackCommand)
	{
		
	}

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

void UActionsWidget::OnAttackClicked()
{
}

void UActionsWidget::OnMagicClicked()
{
}

void UActionsWidget::OnSkillClicked()
{
}

void UActionsWidget::OnItemClicked()
{
}
