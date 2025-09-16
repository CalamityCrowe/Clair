// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/UnitBaseCharacter.h"
#include "PartyUnitBase.generated.h"

USTRUCT(BlueprintType)
struct FPartyUnitStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxHP;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxMP;
	UPROPERTY(EditDefaultsOnly)
	int32 Speed;
	UPROPERTY(EditDefaultsOnly)
	int32 Strength;
	UPROPERTY(EditDefaultsOnly)
	int32 Magic;
	UPROPERTY(EditDefaultsOnly)
	int32 Spirit;
};

USTRUCT(BlueprintType)
struct FPartyUnitRow :public FTableRowBase
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditDefaultsOnly)
	FPartyUnitStats Stats;
};
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

	virtual void IntializeAttributes() override;


private: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PartyData", meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> PartyUnitDataTable;


};
