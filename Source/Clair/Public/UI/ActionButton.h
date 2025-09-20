// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionDelegate);


/**
 * 
 */
class UButton;
class UTextBlock;

UCLASS()
class CLAIR_API UActionButton : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UActionButton();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	FActionDelegate ActionDelegateHandle;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ActionButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionText;

	UFUNCTION()
	void OnActionClicked();
	UFUNCTION()
	void OnReleased(); 
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
