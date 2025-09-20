// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageWidgetTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API UDamageWidgetTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UDamageWidgetTextComponent();
	
	UFUNCTION()
	void SetDamageText(float Damage);
}
;