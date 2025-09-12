// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEnded);

class AUnitBaseCharacter;
class UUnitBattleHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLAIR_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	void StartUnitTurn();
	void EndUnitTurn();
	void BeginBattle();
	void RequestTurn(); 

	FOnTurnEnded OnTurnEnded;

	FTimerHandle& GetActionTimer() { return ActionTimer; }

private: 

	TObjectPtr <AUnitBaseCharacter> UnitCharacter;
		
	FTransform StartingTransform;
	FTimerHandle ActionTimer;

	UPROPERTY(EditDefaultsOnly,Category = "UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUnitBattleHUD> ActionWidgetClass;
	TObjectPtr<UUnitBattleHUD> ActionWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MaxActionTime = 3.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MinActionTime = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraBlendTime = 1.0f;

	void SetCamera(); 
};
