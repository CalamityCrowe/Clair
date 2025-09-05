// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/UnitBaseCharacter.h"
#include "EnemyUnitBase.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API AEnemyUnitBase : public AUnitBaseCharacter
{
	GENERATED_BODY()
public: 
	AEnemyUnitBase();
protected: 
	virtual void BeginPlay() override;
};
