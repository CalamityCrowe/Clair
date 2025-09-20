// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Data/ButtonMaterialManager.h"

UButtonMaterialManager* UButtonMaterialManager::ButtonMaterialManager = nullptr;

UButtonMaterialManager* UButtonMaterialManager::Get()
{
	if (!ButtonMaterialManager)
	{
		ButtonMaterialManager = NewObject<UButtonMaterialManager>();
		ButtonMaterialManager->AddToRoot(); // Prevent garbage collection
		ButtonMaterialManager->Initialize();
	}
	return ButtonMaterialManager;
}
FButtonStyle UButtonMaterialManager::GetButtonStyle(TObjectPtr<UMaterialInstanceDynamic>& OutMat) 
{
	if (!ButtonMaterialInterface)
	{
		return FButtonStyle();
	}
	UMaterialInstanceDynamic* MI = UMaterialInstanceDynamic::Create(ButtonMaterialInterface, this);
	OutMat = MI;

	FSlateBrush Brush;
	Brush.SetResourceObject(OutMat);
	Brush.ImageSize = FVector2D(64, 64);
	Brush.DrawAs = ESlateBrushDrawType::Image;

	ButtonStyle.SetNormal(Brush);
	ButtonStyle.SetHovered(Brush);
	ButtonStyle.SetPressed(Brush);
	// I want the tint colour to be an offset white
	ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f, 1.f));

	// Sounds
	if (HoverSound)
	{
		FSlateSound HoverSlateSound;
		HoverSlateSound.SetResourceObject(HoverSound);
		ButtonStyle.SetHoveredSound(HoverSlateSound);
	}
	if (ClickSound)
	{
		FSlateSound ClickSlateSound;
		ClickSlateSound.SetResourceObject(ClickSound);
		ButtonStyle.SetPressedSound(ClickSlateSound);
	}
	return ButtonStyle;
}
void UButtonMaterialManager::Initialize()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatFinder(TEXT("/Game/UI/Material/MI_Gradient.MI_Gradient"));
	if (MatFinder.Succeeded())
	{
		ButtonMaterialInterface = MatFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> HoverSoundFinder(TEXT("/Game/SoundEffects/UI/MenuSounds.MenuSounds"));
	if (HoverSoundFinder.Succeeded())
	{
		HoverSound = HoverSoundFinder.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundBase> ClickSoundFinder(TEXT("/Game/SoundEffects/UI/MenuSelect.MenuSelect"));
	if (ClickSoundFinder.Succeeded())
	{
		ClickSound = ClickSoundFinder.Object;
	}

}
