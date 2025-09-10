// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BattlePlayerController.h"

ABattlePlayerController::ABattlePlayerController()
{
	bAutoManageActiveCameraTarget = false;
	bShowMouseCursor = true; 
}

void ABattlePlayerController::BeginPlay()
{
	Super::BeginPlay();
}
