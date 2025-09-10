// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BattlePlayerController.h"
#include "UI/BattleHUD.h"
#include "Gamefiles/ClairGamemode.h"

ABattlePlayerController::ABattlePlayerController()
{
	bAutoManageActiveCameraTarget = false;
	bShowMouseCursor = true;
}

void ABattlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (BattleHUDClass)
	{
		BattleHUD = CreateWidget<UBattleHUD>(this, BattleHUDClass);
		if (BattleHUD)
		{
			BattleHUD->AddToViewport();

			AClairGamemode* GM = Cast<AClairGamemode>(GetWorld()->GetAuthGameMode());
			GM->SetupBattleHUD(BattleHUD);

		}
	}
}
