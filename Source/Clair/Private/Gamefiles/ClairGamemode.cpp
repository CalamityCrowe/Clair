// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamefiles/ClairGamemode.h"
#include "Characters/UnitBaseCharacter.h"
#include "Characters/Party/PartyUnitBase.h"
#include "Characters/Enemy/EnemyUnitBase.h"
#include "Components/CombatComponent.h"
#include "Actors/TopDownCamera.h"
#include "Kismet/GameplayStatics.h"

AClairGamemode::AClairGamemode()
{

}

void AClairGamemode::BeginPlay()
{
	Super::BeginPlay();
	MainBattleCamera = Cast<ATopDownCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), ATopDownCamera::StaticClass()));
	if (MainBattleCamera)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(MainBattleCamera, 2.0f);
	}

	TArray<AActor*> FoundUnits;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnitBaseCharacter::StaticClass(), FoundUnits);
	for (AActor* Unit : FoundUnits)
	{
		if (APartyUnitBase* PartyUnit = Cast<APartyUnitBase>(Unit))
		{
			PartyUnits.AddUnique(PartyUnit);
		}
		else if (AEnemyUnitBase* EnemyUnit = Cast<AEnemyUnitBase>(Unit))
		{
			EnemyUnits.AddUnique(EnemyUnit);
		}
	}
}

void AClairGamemode::TurnRequest(AUnitBaseCharacter* Unit)
{
	TurnOrder.AddUnique(Unit);

	StartTurn();
}

void AClairGamemode::StartTurn()
{
	if (bStartTurn)
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
