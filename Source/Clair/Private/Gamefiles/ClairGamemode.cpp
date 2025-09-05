// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamefiles/ClairGamemode.h"
#include "Characters/UnitBaseCharacter.h"
#include "Components/CombatComponent.h"

AClairGamemode::AClairGamemode()
{

}

void AClairGamemode::BeginPlay()
{
	Super::BeginPlay();
}

void AClairGamemode::TurnRequest(AUnitBaseCharacter* Unit)
{
	TurnOrder.AddUnique(Unit);

	StartTurn();
}

void AClairGamemode::StartTurn()
{
	if(bStartTurn)
	{
		if (TurnOrder.IsValidIndex(0))
		{
			TurnOrder[0]->GetCombatComponent()->StartUnitTurn();
			bStartTurn = false;
			// bind to end turn event
			TurnOrder[0]->GetCombatComponent()->OnTurnEnded.AddDynamic(this, &AClairGamemode::ReadyNextTurn);
			TurnOrder.RemoveAt(0); 
			bStartTurn = false;
		}
		else
		{
			bStartTurn = true;
			if (TurnOrder.IsValidIndex(0)) 
			{
				StartTurn(); 
			}
		}
	}
}

void AClairGamemode::ReadyNextTurn()
{

}
