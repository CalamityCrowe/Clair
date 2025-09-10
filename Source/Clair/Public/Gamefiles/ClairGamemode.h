// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ClairGamemode.generated.h"

/**
 * 
 */
class AUnitBaseCharacter;
class APartyUnitBase;
class AEnemyUnitBase;
class ATopDownCamera;

UCLASS()
class CLAIR_API AClairGamemode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AClairGamemode();

	virtual void BeginPlay() override;

	virtual void TurnRequest(AUnitBaseCharacter* Unit); 

private: 

	virtual void StartTurn();
	virtual void ReadyNextTurn();

	bool bStartTurn; 

	TArray<AUnitBaseCharacter*> TurnOrder;
	TArray<TObjectPtr<APartyUnitBase>> PartyUnits;
	TArray<TObjectPtr<AEnemyUnitBase>> EnemyUnits;


	ATopDownCamera* MainBattleCamera;
};
