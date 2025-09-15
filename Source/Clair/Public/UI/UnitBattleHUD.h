// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitBattleHUD.generated.h"

class UBackgroundBlur;
class UVerticalBox;
class UBorder;
class UActionsWidget; 
class UTargetWindow; 

/**
 * 
 */
UCLASS()
class CLAIR_API UUnitBattleHUD : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	UUnitBattleHUD();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetBoundCharacter(class AUnitBaseCharacter* NewCharacter);
protected: 
	TObjectPtr<AUnitBaseCharacter> BoundCharacter;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UActionsWidget> ActionsCommands;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTargetWindow> TargetWindow;
	// create a u property to bind an animation
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> ShowTargetAnim;


	UFUNCTION()
	void ShowTargetWindow();
	UFUNCTION()
	void HideTargetWindow();
};
