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
class UBattleHUD;
UCLASS()
class CLAIR_API AClairGamemode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AClairGamemode();

	virtual void BeginPlay() override;

	virtual void TurnRequest(AUnitBaseCharacter* Unit); 

	void SetupBattleHUD(UBattleHUD* );

	float GetTimerDelay() const { return TimerDelay; }
private: 

	virtual void StartTurn();
	UFUNCTION()
	virtual void ReadyNextTurn();

	bool bStartTurn; 

	UPROPERTY(EditDefaultsOnly, Category = "Timer")
	float TimerDelay; 

	TArray<AUnitBaseCharacter*> TurnOrder;
	TArray<TObjectPtr<APartyUnitBase>> PartyUnits;
	TArray<TObjectPtr<AEnemyUnitBase>> EnemyUnits;

	TObjectPtr<UBattleHUD> BattleHUD;

	ATopDownCamera* MainBattleCamera;
};
