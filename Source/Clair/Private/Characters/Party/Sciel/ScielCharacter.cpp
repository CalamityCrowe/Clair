// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Party/Sciel/ScielCharacter.h"

AScielCharacter::AScielCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	CharacterName = FText::FromString("Sciel");
}

void AScielCharacter::BeginPlay()
{
	Super::BeginPlay();

}