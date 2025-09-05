// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/UnitBaseCharacter.h"
#include "PartyUnitBase.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API APartyUnitBase : public AUnitBaseCharacter
{
	GENERATED_BODY()
public: 
	APartyUnitBase();
protected: 
	virtual void BeginPlay() override;


};
