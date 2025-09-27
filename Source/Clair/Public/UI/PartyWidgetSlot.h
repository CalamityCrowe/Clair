// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyWidgetSlot.generated.h"

class UVerticalBox;
class UHorizontalBox;
class UTextBlock;
class UProgressBar;
class AUnitBaseCharacter;
class UAsyncTaskAttributeChange;

/**
 * 
 */
UCLASS()
class CLAIR_API UPartyWidgetSlot : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UPartyWidgetSlot();

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void BindToCharacter(AUnitBaseCharacter* Character);

protected: 

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MainBox;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* NameBox;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPNumber;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHPNumber;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MPText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MPNumber;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxMPNumber;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* TurnBar;


	UPROPERTY()
	TObjectPtr<AUnitBaseCharacter> BoundCharacter;

	UFUNCTION(BlueprintPure)
	float UpdateProgressBar();

private: 
	UPROPERTY()
	TObjectPtr<UAsyncTaskAttributeChange> AttributeChangeTask;
	UFUNCTION()
	void UpdateHealth(FGameplayAttribute Attribute, float NewValue, float MaxValue);
	UFUNCTION()
	void UpdateMana(FGameplayAttribute Attribute, float NewValue, float OldValue);

	float CurrentHP;
	float TargetHP;
	float OldHP;

	FTimerHandle StatUpdateTimerHandle;

	void UpdateHealthText();

	//UPROPERTY(meta = (BindWidget))
	//UProgressBar* MPBar;
};
