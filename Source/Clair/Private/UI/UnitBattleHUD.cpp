// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UnitBattleHUD.h"
#include "UI/ActionsWidget.h"
#include "UI/TargetWindow.h"
#include "UI/ActionButton.h"

UUnitBattleHUD::UUnitBattleHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UUnitBattleHUD::NativeConstruct()
{
	Super::NativeConstruct();
	ActionsCommands->GetAttackCommand()->ActionDelegateHandle.AddDynamic(this,&UUnitBattleHUD::ShowTargetWindow);
	TargetWindow->GetBackButton()->ActionDelegateHandle.AddDynamic(this, &UUnitBattleHUD::HideTargetWindow);
}
void UUnitBattleHUD::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUnitBattleHUD::SetBoundCharacter(AUnitBaseCharacter* NewCharacter)
{
	if (ActionsCommands)
	{
		ActionsCommands->SetBoundCharacter(NewCharacter);
	}
}

void UUnitBattleHUD::ShowTargetWindow()
{
	if (TargetWindow)
	{
		PlayAnimationForward(ShowTargetAnim);
		TargetWindow->PopulateTargetList();
	}
}

void UUnitBattleHUD::HideTargetWindow()
{
	if (TargetWindow)
	{
		PlayAnimationReverse(ShowTargetAnim);
	}
}
