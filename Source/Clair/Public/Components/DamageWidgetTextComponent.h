// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageWidgetTextComponent.generated.h"

class UDamageNumberWidget;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CLAIR_API UDamageWidgetTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UDamageWidgetTextComponent();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetDamageText(float Damage);

	void SetDamageWidgetClass(TSubclassOf<UDamageNumberWidget> InDamageWidgetClass); 
}
;