// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BattleAIController.h"

ABattleAIController::ABattleAIController()
{
}

void ABattleAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (MoveToAttackDelegate.IsBound())
	{
		MoveToAttackDelegate.Broadcast();
		MoveToAttackDelegate.Clear();
	}
	if (MoveToStartDelegate.IsBound())
	{
		MoveToStartDelegate.Broadcast();
		MoveToStartDelegate.Clear();
	}

}
