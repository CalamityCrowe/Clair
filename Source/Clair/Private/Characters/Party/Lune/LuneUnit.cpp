// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Party/Lune/LuneUnit.h"

ALuneUnit::ALuneUnit()
{
	// Set default properties specific to Lune here

	CharacterName = FText::FromString("Lune");

}

void ALuneUnit::BeginPlay()
{
	Super::BeginPlay();
	// Additional initialization for Lune can be done here
}