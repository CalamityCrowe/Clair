// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetWindow.generated.h"

class UBackgroundBlur;
class UVerticalBox;
class UBorder;
class UTextBlock;
class UScrollBox;
class AUnitBaseCharacter;
class UTargetWindowSlot;

class UActionButton;



/**
 * 
 */
UCLASS()
class CLAIR_API UTargetWindow : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	UTargetWindow();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetBoundCharacter(class AUnitBaseCharacter* NewCharacter);

	void PopulateTargetList();

	TObjectPtr<UActionButton> GetBackButton() const { return BackButton; }

protected: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> BackgroundBlur;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> NameBorder;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> TargetsBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> TargetsList;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTargetWindowSlot> TargetSlotClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UActionButton> BackButton;
private: 
	TObjectPtr<AUnitBaseCharacter> BoundCharacter;
	UFUNCTION()
	void SetTarget(AUnitBaseCharacter* Target);
};
