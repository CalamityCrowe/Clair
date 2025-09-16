// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Party/PartyUnitBase.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "Characters/Abilities/ClairAbilitySystemComponent.h"
APartyUnitBase::APartyUnitBase()
{
}

void APartyUnitBase::BeginPlay()
{
	Super::BeginPlay();
	if(ASC)
	{
		IntializeAttributes(); 
		SetHealth(GetMaxHealth()); 
		SetMana(GetMaxMana()); 
	}

}

void APartyUnitBase::IntializeAttributes()
{
	// this is where we will initialize the attributes from the data table
	if (!ASC || !PartyUnitDataTable) return; 
	FName RowName = *CharacterName.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Row Name: %s"), *RowName.ToString()));

	const FPartyUnitRow* DefaultRow = PartyUnitDataTable->FindRow<FPartyUnitRow>(RowName, TEXT("Init"));
	if (!DefaultRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Row found for %s"), *RowName.ToString());
		return;
	}
	const FPartyUnitStats& DefaultStats = DefaultRow->Stats; // access the nested struct


	ASC->SetNumericAttributeBase(AttributeSetBase->GetMaxHealthAttribute(), DefaultStats.MaxHP);
	ASC->SetNumericAttributeBase(AttributeSetBase->GetMaxManaAttribute(), DefaultStats.MaxMP);
	ASC->SetNumericAttributeBase(AttributeSetBase->GetSpeedAttribute(), DefaultStats.Speed);
	ASC->SetNumericAttributeBase(AttributeSetBase->GetStrengthAttribute(), DefaultStats.Strength);
	ASC->SetNumericAttributeBase(AttributeSetBase->GetMagicAttribute(), DefaultStats.Magic);
	ASC->SetNumericAttributeBase(AttributeSetBase->GetSpiritAttribute(), DefaultStats.Spirit);
}
