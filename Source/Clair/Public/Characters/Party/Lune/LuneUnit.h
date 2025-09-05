// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Party/PartyUnitBase.h"
#include "LuneUnit.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API ALuneUnit : public APartyUnitBase
{
	GENERATED_BODY()
public: 
	ALuneUnit();

protected:
	virtual void BeginPlay() override;
};
