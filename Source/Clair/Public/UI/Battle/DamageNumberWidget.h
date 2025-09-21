// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageNumberWidget.generated.h"

class UTextBlock;
class UOverlay;
class URetainerBox;
class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class CLAIR_API UDamageNumberWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	UDamageNumberWidget();

	virtual void NativeConstruct() override;

	void SetDamageNumber(int32 Damage, bool bIsCritical, bool bIsHeal);

protected: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DamageText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> DamageOverlay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URetainerBox> RetainerBox;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeOutAnimation;


};
