// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattlePlayerController.generated.h"

class UBattleHUD;
/**
 * 
 */
UCLASS()
class CLAIR_API ABattlePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABattlePlayerController();


	UBattleHUD* GetBattleHUD() const { return BattleHUD; }

	void CreateBattleHUD();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UBattleHUD> BattleHUDClass;

	TObjectPtr<UBattleHUD> BattleHUD;


};
