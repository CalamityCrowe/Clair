// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ClairAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRecievedDamageDelegate, UClairAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

/**
 * 
 */
UCLASS()
class CLAIR_API UClairAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public: 

	bool bCharacterAbilitiesGiven = false; 
	bool bStartupEffectsApplied = false;

	FRecievedDamageDelegate RecievedDamage; 

	virtual void RecieveDamage(UClairAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);
};
