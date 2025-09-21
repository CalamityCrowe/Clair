// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageWidgetTextComponent.h"
#include "UI/Battle/DamageNumberWidget.h"


UDamageWidgetTextComponent::UDamageWidgetTextComponent()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawSize(FVector2D(300.f, 200.f));
	SetTwoSided(true);
	SetVisibility(true);
	SetHiddenInGame(false);

}

void UDamageWidgetTextComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDamageWidgetTextComponent::SetDamageText(float Damage)
{
	if (UDamageNumberWidget* DamageWidget = Cast<UDamageNumberWidget>(GetUserWidgetObject())) 
	{
		DamageWidget->SetDamageNumber(Damage, false, false);
		FTimerHandle Handle;
		// set a timer to destroy this component after one second
		GetWorld()->GetTimerManager().SetTimer(Handle, [this]() { DestroyComponent(); }, 1.0f, false); 
	}
}

void UDamageWidgetTextComponent::SetDamageWidgetClass(TSubclassOf<UDamageNumberWidget> InDamageWidgetClass)
{
	SetWidgetClass(InDamageWidgetClass);
}
