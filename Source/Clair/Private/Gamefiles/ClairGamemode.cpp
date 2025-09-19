// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamefiles/ClairGamemode.h"
#include "Characters/UnitBaseCharacter.h"
#include "Characters/Party/PartyUnitBase.h"
#include "Characters/Enemy/EnemyUnitBase.h"
#include "Components/CombatComponent.h"
#include "Actors/TopDownCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BattlePlayerController.h"
#include "UI/BattleHUD.h"


AClairGamemode::AClairGamemode()
{
	bStartTurn = true;
}

void AClairGamemode::BeginPlay()
{
	Super::BeginPlay();

	if (BattleMusic)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BattleMusic);
	}

	MainBattleCamera = Cast<ATopDownCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), ATopDownCamera::StaticClass()));
	if (MainBattleCamera)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(MainBattleCamera, TimerDelay);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
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

			if (ABattlePlayerController* PC = Cast<ABattlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
			{
				PC->CreateBattleHUD();
				if (PC->GetBattleHUD())
				{
					for (APartyUnitBase* Unit : PartyUnits)
					{
						PC->GetBattleHUD()->AddPartyToHUD(Unit);
					}
				}
			}

			}, TimerDelay, false);
	}


}

void AClairGamemode::TurnRequest(AUnitBaseCharacter* Unit)
{
	TurnOrder.AddUnique(Unit);

	StartTurn();
}

void AClairGamemode::SetupBattleHUD(UBattleHUD* BHUD)
{
	BattleHUD = BHUD;
	if (BattleHUD)
	{
		for (APartyUnitBase* Unit : PartyUnits)
		{
			BattleHUD->AddPartyToHUD(Unit);
		}
	}
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
			if (!TurnOrder[0]->GetCombatComponent()->OnTurnEnded.IsAlreadyBound(this, &AClairGamemode::ReadyNextTurn))
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
	bStartTurn = true;
	if (TurnOrder.IsValidIndex(0))
	{
		StartTurn();
	}
}
