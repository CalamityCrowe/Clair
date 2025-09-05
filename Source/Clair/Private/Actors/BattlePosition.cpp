// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BattlePosition.h"
#include "Components/ArrowComponent.h"
#include "Characters/UnitBaseCharacter.h"

// Sets default values
ABattlePosition::ABattlePosition()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

	FLinearColor Color = (bIsEnemyPlacement ? FLinearColor::Red : FLinearColor::Green);
	ArrowComponent->SetArrowColor(Color);
}

// Called when the game starts or when spawned
void ABattlePosition::BeginPlay()
{
	Super::BeginPlay();
	SpawnUnit(); 
}

void ABattlePosition::SpawnUnit()
{
	if(UnitClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<AUnitBaseCharacter>(UnitClass, GetActorTransform(), SpawnParams);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitClass is not set for BattlePosition at location: %s"), *GetActorLocation().ToString());
	}
}


