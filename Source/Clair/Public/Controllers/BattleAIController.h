// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleAIController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveCompletedDelegate);


class UDamageNumberWidget;
class AUnitBaseCharacter;
/**
 * 
 */
UCLASS()
class CLAIR_API ABattleAIController : public AAIController
{
	GENERATED_BODY()
public: 
	ABattleAIController();

	FOnMoveCompletedDelegate MoveToAttackDelegate;
	FOnMoveCompletedDelegate MoveToStartDelegate;

	void ShowDamageNumber(float Damage, bool bIsCritical, bool bIsHeal, AUnitBaseCharacter* Target);

private: 

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDamageNumberWidget> DamageNumberWidgetClass;
};
