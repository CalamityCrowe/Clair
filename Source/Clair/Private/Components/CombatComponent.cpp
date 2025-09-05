// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"
#include "Characters/UnitBaseCharacter.h"
UCombatComponent::UCombatComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	UnitCharacter = Cast<AUnitBaseCharacter>(GetOwner());
	StartingTransform = GetOwner()->GetActorTransform();
}

void UCombatComponent::StartUnitTurn()
{
}

void UCombatComponent::EndUnitTurn()
{
}

void UCombatComponent::BeginBattle()
{
}


