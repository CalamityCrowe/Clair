// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleHUD.generated.h"

class UPartyWidget;
class UPartyWidgetSlot;
class AUnitBaseCharacter;


/**
 * 
 */
UCLASS()
class CLAIR_API UBattleHUD : public UUserWidget
{
	GENERATED_UCLASS_BODY()
	
public: 
	UBattleHUD();
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void AddPartyToHUD(AUnitBaseCharacter* UnitBase);

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPartyWidgetSlot> PartyWidgetSlotClass;

	UPROPERTY(meta = (BindWidget))
	UPartyWidget* PartyWidget;
};
