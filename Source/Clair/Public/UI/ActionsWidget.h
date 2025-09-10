// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionsWidget.generated.h"

/**
 * 
 */
class UBackgroundBlur;
class UVerticalBox;
class UBorder;
class UTextBlock;
class UActionButton;
class AUnitBaseCharacter;


UCLASS()
class CLAIR_API UActionsWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UActionsWidget();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetBoundCharacter(AUnitBaseCharacter* NewCharacter);

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> BackgroundBlur;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> NameBorder;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ActionsBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UActionButton> AttackCommand;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UActionButton> MagicCommand;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UActionButton> SkillCommand;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UActionButton> ItemCommand;

	TObjectPtr<AUnitBaseCharacter> BoundCharacter;
};
