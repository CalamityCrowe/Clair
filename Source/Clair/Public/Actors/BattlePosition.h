// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattlePosition.generated.h"
class UArrowComponent;
class AUnitBaseCharacter; 

UCLASS()
class CLAIR_API ABattlePosition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattlePosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	bool IsEnemyPlacement() const { return bIsEnemyPlacement; }
	void SetIsEnemyPlacement(bool bIsEnemy) { bIsEnemyPlacement = bIsEnemy; }


private: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UArrowComponent> ArrowComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit", meta = (AllowPrivateAccess = true))
	TSubclassOf<AUnitBaseCharacter> UnitClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit", meta = (AllowPrivateAccess = true))
	bool bIsEnemyPlacement;

	void SpawnUnit();
};
