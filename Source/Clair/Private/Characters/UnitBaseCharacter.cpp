// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UnitBaseCharacter.h"
#include "Components/CombatComponent.h"
// Sets default values
AUnitBaseCharacter::AUnitBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

// Called when the game starts or when spawned
void AUnitBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

