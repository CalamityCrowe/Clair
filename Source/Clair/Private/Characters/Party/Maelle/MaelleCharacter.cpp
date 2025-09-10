// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Party/Maelle/MaelleCharacter.h"

AMaelleCharacter::AMaelleCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	CharacterName = FText::FromString("Maelle");
}

void AMaelleCharacter::BeginPlay()
{
	Super::BeginPlay();

}