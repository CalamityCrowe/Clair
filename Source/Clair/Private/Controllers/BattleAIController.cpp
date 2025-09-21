// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BattleAIController.h"
#include "Components/DamageWidgetTextComponent.h"
#include "UI/Battle/DamageNumberWidget.h"
#include "Characters/UnitBaseCharacter.h"

ABattleAIController::ABattleAIController()
{
}

void ABattleAIController::ShowDamageNumber(float Damage, bool bIsCritical, bool bIsHeal, AUnitBaseCharacter* Target)
{
	if (DamageNumberWidgetClass)
	{
		UDamageWidgetTextComponent* DamageText = NewObject<UDamageWidgetTextComponent>(Target);

		DamageText->SetDamageWidgetClass(DamageNumberWidgetClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(Target->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->SetDamageText(Damage);

	}
}

void ABattleAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (MoveToAttackDelegate.IsBound())
	{
		MoveToAttackDelegate.Broadcast();
		MoveToAttackDelegate.Clear();
	}
	if (MoveToStartDelegate.IsBound())
	{
		MoveToStartDelegate.Broadcast();
		MoveToStartDelegate.Clear();
	}

}
