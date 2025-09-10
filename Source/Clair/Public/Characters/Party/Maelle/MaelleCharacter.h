// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Party/PartyUnitBase.h"
#include "MaelleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API AMaelleCharacter : public APartyUnitBase
{
	GENERATED_BODY()
public: 
	AMaelleCharacter();

protected:
	virtual void BeginPlay() override;

	
};
