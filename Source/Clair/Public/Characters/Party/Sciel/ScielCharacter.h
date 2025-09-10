// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Party/PartyUnitBase.h"
#include "ScielCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API AScielCharacter : public APartyUnitBase
{
	GENERATED_BODY()
public: 
	AScielCharacter();
protected:

	virtual void BeginPlay() override;
};
