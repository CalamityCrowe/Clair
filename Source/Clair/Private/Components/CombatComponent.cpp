// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"
#include "Characters/UnitBaseCharacter.h"
#include "Characters/Party/PartyUnitBase.h"
#include "Gamefiles/ClairGamemode.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/ActionsWidget.h"


UCombatComponent::UCombatComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> ActionWidgetBPClass(TEXT("/Game/UI/WBP_Actions"));
	if (ActionWidgetBPClass.Class != nullptr)
	{
		ActionWidgetClass = ActionWidgetBPClass.Class;
	}
	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	UnitCharacter = Cast<AUnitBaseCharacter>(GetOwner());
	StartingTransform = GetOwner()->GetActorTransform();

	FTimerHandle TimerHandle;
	float GMDelay = GetWorld()->GetAuthGameMode<AClairGamemode>()->GetTimerDelay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
		BeginBattle();
		}, GMDelay, false);
}

void UCombatComponent::StartUnitTurn()
{
	// print the unit character's name to the screen for 2 seconds
	if (APartyUnitBase* PartyUnit = Cast<APartyUnitBase>(UnitCharacter)) 
	{
		ActionWidget = CreateWidget<UActionsWidget>(GetWorld(), ActionWidgetClass);
		if (ActionWidget)
		{
			ActionWidget->AddToViewport();
			ActionWidget->SetBoundCharacter(PartyUnit);
		}
	}
}

void UCombatComponent::EndUnitTurn()
{
}

void UCombatComponent::BeginBattle()
{
	float Timer = UnitCharacter->GetAgility();
	Timer = UKismetMathLibrary::NormalizeToRange(Timer, 0.0f, 255.0f);
	Timer = ((1 - Timer) * (MaxActionTime - MinActionTime) + MinActionTime) ;

	GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &UCombatComponent::RequestTurn, Timer, false);
}

void UCombatComponent::RequestTurn()
{
	if (AClairGamemode* GM = GetWorld()->GetAuthGameMode<AClairGamemode>())
	{
		GM->TurnRequest(UnitCharacter); 
	}

}


