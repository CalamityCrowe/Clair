// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyWidget.generated.h"

class UPartyWidgetSlot;
class UBorder;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class CLAIR_API UPartyWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 

	UPartyWidget(); 

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	UBorder* BorderBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PartyBox;
};
