// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PhysicalDamageExecCalculation.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API UPhysicalDamageExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public: 
	UPhysicalDamageExecCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
