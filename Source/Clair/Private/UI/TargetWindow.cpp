// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TargetWindow.h"
#include "Components/BackgroundBlur.h"
#include "Components/VerticalBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Gamefiles/ClairGamemode.h"
#include "Characters/Enemy/EnemyUnitBase.h"
#include "UI/TargetWindowSlot.h"

UTargetWindow::UTargetWindow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UTargetWindow::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTargetWindow::NativeDestruct()
{
	Super::NativeDestruct();
}

void UTargetWindow::PopulateTargetList()
{
	TargetsList->ClearChildren();
	AClairGamemode* GM = GetWorld()->GetAuthGameMode<AClairGamemode>();
	if (GM) 
	{
		for (AEnemyUnitBase* Enemy : GM->GetEnemyUnits())
		{
			UTargetWindowSlot* NewSlot = CreateWidget<UTargetWindowSlot>(GetWorld(), TargetSlotClass);
			if (NewSlot)
			{
				NewSlot->SetBoundCharacter(Enemy);
				TargetsList->AddChild(NewSlot);
			}
		}
	}
}
