// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TargetWindowSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Characters/UnitBaseCharacter.h"
#include "UI/Data/ButtonMaterialManager.h"

UTargetWindowSlot::UTargetWindowSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
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

void UTargetWindowSlot::NativeConstruct()
{
	Super::NativeConstruct();
	if (SlotButton)
	{
		SlotButton->SetStyle(ButtonStyle);
		SlotButton->OnClicked.AddDynamic(this, &UTargetWindowSlot::OnSlotClicked);
		SlotButton->OnHovered.AddDynamic(this, &UTargetWindowSlot::OnHovered);
		SlotButton->OnUnhovered.AddDynamic(this, &UTargetWindowSlot::OnUnhovered);
	}
}

void UTargetWindowSlot::NativeDestruct()
{
	Super::NativeDestruct();
}

void UTargetWindowSlot::SetBoundCharacter(AUnitBaseCharacter* NewCharacter)
{
	BoundCharacter = NewCharacter;
	if (BoundCharacter)
	{
		SlotText->SetText(BoundCharacter->GetCharacterName());
	}
}

void UTargetWindowSlot::OnSlotClicked()
{
	TargetChosen.Broadcast(BoundCharacter);
}

void UTargetWindowSlot::OnHovered()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(FillTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(FillTimerHandle);
	}
	bIsFilling = true;
	GetWorld()->GetTimerManager().SetTimer(FillTimerHandle, this, &UTargetWindowSlot::HoveredFill, 0.01f, true);
}

void UTargetWindowSlot::OnUnhovered()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(FillTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(FillTimerHandle);
	}
	bIsFilling = false;
	GetWorld()->GetTimerManager().SetTimer(FillTimerHandle, this, &UTargetWindowSlot::HoveredFill, 0.01f, true);
}

void UTargetWindowSlot::HoveredFill()
{
	Elapsed += bIsFilling ? 0.05 : -0.02;
	float Alpha = FMath::Clamp(Elapsed / Duration, 0, 1);
	CurrentFill = FMath::Lerp(MaxFill, 2, Alpha);
	ButtonMaterial->SetScalarParameterValue(FName("Fill"), CurrentFill);
	if (bIsFilling)
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
