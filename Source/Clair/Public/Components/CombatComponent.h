// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEnded);

class AUnitBaseCharacter;
class UUnitBattleHUD;
class ABattleAIController;


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

	void AttackCommand(); 
	void ReturnToStart();


	FOnTurnEnded OnTurnEnded;

	FTimerHandle& GetActionTimer() { return ActionTimer; }

	void SetTarget(AUnitBaseCharacter* NewTarget) { UnitTarget = NewTarget; }

private: 

	TObjectPtr <AUnitBaseCharacter> UnitCharacter;
	TObjectPtr <AUnitBaseCharacter> UnitTarget;
	TObjectPtr<ABattleAIController> BattleController;
		
	FTransform StartingTransform;
	FTimerHandle ActionTimer;

	bool bIsRanged; 

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

	void MeleeAttack(); 
	void RangedAttack();

	UFUNCTION()
	void MovementComplete();
	UFUNCTION()
	void ResetRotation(); 
};
