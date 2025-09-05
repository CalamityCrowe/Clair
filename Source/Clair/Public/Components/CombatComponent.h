// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEnded);

class AUnitBaseCharacter;

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

	FOnTurnEnded OnTurnEnded;

private: 

	TObjectPtr <AUnitBaseCharacter> UnitCharacter;
		
	FTransform StartingTransform;

};
