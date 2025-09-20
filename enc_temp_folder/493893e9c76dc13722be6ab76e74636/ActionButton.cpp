// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActionButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/Data/ButtonMaterialManager.h"

UActionButton::UActionButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// loading in a material instance from the editor using the constructor helper
	if (UButtonMaterialManager::Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("Button Material Manager Loaded Successfully"));
	}
	ButtonStyle = UButtonMaterialManager::Get()->GetButtonStyle(ButtonMaterial);
	Duration = 0.4;
	Elapsed = 0.0f;
	MaxFill = 20.f; 
	MinFill = 0.5f;
}

void UActionButton::NativeConstruct()
{
	Super::NativeConstruct();
	if(ActionButton)
	{
		ActionButton->SetStyle(ButtonStyle);
		ActionButton->OnClicked.AddDynamic(this, &UActionButton::OnActionClicked);
		ActionButton->OnPressed.AddDynamic(this, &UActionButton::OnReleased);
		ActionButton->OnHovered.AddDynamic(this, &UActionButton::OnHovered);
		ActionButton->OnUnhovered.AddDynamic(this, &UActionButton::OnUnhovered);
	}

}
void UActionButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UActionButton::OnActionClicked()
{
	ActionDelegateHandle.Broadcast();
}

void UActionButton::OnReleased()
{
}

void UActionButton::OnHovered()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(FillTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(FillTimerHandle);
	}
	bIsFilling = true;
	GetWorld()->GetTimerManager().SetTimer(FillTimerHandle, this, &UActionButton::HoveredFill, 0.01f, true);
}

void UActionButton::OnUnhovered()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(FillTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(FillTimerHandle);
	}
	bIsFilling = false;
	GetWorld()->GetTimerManager().SetTimer(FillTimerHandle, this, &UActionButton::HoveredFill, 0.01f, true);
}

void UActionButton::HoveredFill()
{

	Elapsed += bIsFilling? 0.05:-0.02;
	float Alpha = FMath::Clamp(Elapsed / Duration, 0, 1);
	CurrentFill = FMath::Lerp(MaxFill, 2, Alpha);
	ButtonMaterial->SetScalarParameterValue(FName("Fill"), CurrentFill);
	if(bIsFilling)
	{
		if (Alpha >= 1.0f)
		{
			GetWorld()->GetTimerManager().ClearTimer(FillTimerHandle);
		}
	}
	else
	{
		if (Alpha <= 0.0f)
		{
			GetWorld()->GetTimerManager().ClearTimer(FillTimerHandle);
		}
	}
}
