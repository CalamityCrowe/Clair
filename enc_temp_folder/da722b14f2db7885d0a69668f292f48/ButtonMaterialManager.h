// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/NoExportTypes.h"
#include "ButtonMaterialManager.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API UButtonMaterialManager : public UObject
{
	GENERATED_BODY()
public: 
	static UButtonMaterialManager* Get(); 

	
	FButtonStyle GetButtonStyle(TObjectPtr<UMaterialInstanceDynamic>& Mat) ;

	UMaterialInterface* GetButtonMaterial() { return ButtonMaterialInterface; }

private: 

	static UButtonMaterialManager* ButtonMaterialManager;

	UMaterialInterface* ButtonMaterialInterface;

	FButtonStyle ButtonStyle;

	void Initialize();

	TObjectPtr<USoundBase> HoverSound;
	TObjectPtr<USoundBase> ClickSound;

};
