// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetWindowSlot.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetChosen,AUnitBaseCharacter*, Unit);

class UButton; 
class UTextBlock;
class AUnitBaseCharacter;

UCLASS()
class CLAIR_API UTargetWindowSlot : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UTargetWindowSlot();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void SetBoundCharacter(AUnitBaseCharacter* NewCharacter); 

	FOnTargetChosen TargetChosen; 

protected: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SlotText;

	TObjectPtr<AUnitBaseCharacter> BoundCharacter;

	UFUNCTION()
	void OnSlotClicked();
	UFUNCTION()
	void OnHovered(); 
	UFUNCTION()
	void OnUnhovered();

private:



	TObjectPtr<UMaterialInstanceDynamic> ButtonMaterial;
	FButtonStyle ButtonStyle;
	FTimerHandle FillTimerHandle;

	float MaxFill;
	float CurrentFill;
	float MinFill;
	float Duration;
	float Elapsed;
	bool bIsFilling;

	void HoveredFill();
};
