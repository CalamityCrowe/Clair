// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"
#include "Characters/UnitBaseCharacter.h"
#include "Characters/Party/PartyUnitBase.h"
#include "Gamefiles/ClairGamemode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UnitBattleHUD.h"
#include "Actors/DynamicCamera.h"
#include "Controllers/BattleAIController.h"

UCombatComponent::UCombatComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> ActionWidgetBPClass(TEXT("/Game/UI/WBP_UnitBattleHUD"));
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

	if (BattleController = Cast<ABattleAIController>(UnitCharacter->GetController()))
	{
	}

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
		ActionWidget = CreateWidget<UUnitBattleHUD>(GetWorld(), ActionWidgetClass);
		if (ActionWidget)
		{
			ActionWidget->AddToViewport();
			ActionWidget->SetBoundCharacter(PartyUnit);
		}
		SetCamera();
	}
}

void UCombatComponent::EndUnitTurn()
{
	OnTurnEnded.Broadcast();
	BeginBattle();
}

void UCombatComponent::BeginBattle()
{
	float Speed = UnitCharacter->GetSpeed();
	float ATB = UnitCharacter->GetATBTick();
	float Time = (((60 - Speed) * 160)/ATB)/60 ; 
	GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &UCombatComponent::RequestTurn, Time, false);
}

void UCombatComponent::RequestTurn()
{
	if (AClairGamemode* GM = GetWorld()->GetAuthGameMode<AClairGamemode>())
	{
		GM->TurnRequest(UnitCharacter);
	}

}

void UCombatComponent::AttackCommand()
{
	if (bIsRanged)
	{
		RangedAttack();
	}
	else
	{
		MeleeAttack();
	}
}

void UCombatComponent::ReturnToStart()
{

	BattleController->MoveToLocation(StartingTransform.GetLocation(), 1);
	BattleController->MoveToStartDelegate.AddDynamic(this, &UCombatComponent::ResetRotation);
}

void UCombatComponent::SetCamera()
{
	AActor* DynamicCameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADynamicCamera::StaticClass());
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetViewTargetWithBlend(DynamicCameraActor, CameraBlendTime);
	if (ICameraInterface* CameraInterface = Cast<ICameraInterface>(DynamicCameraActor))
	{
		CameraInterface->SetCameraLocation(UnitCharacter, StartingTransform.GetLocation());
	}
}

void UCombatComponent::MeleeAttack()
{
	if (BattleController)
	{
		BattleController->MoveToActor(UnitTarget, 100.f);

		BattleController->MoveToAttackDelegate.AddDynamic(this, &UCombatComponent::MovementComplete);

		if (ActionWidget)
		{
			ActionWidget->RemoveFromParent();
		}
	}

}

void UCombatComponent::RangedAttack()
{
}

void UCombatComponent::MovementComplete()
{
	UnitCharacter->PlayAttackMontage();
}


void UCombatComponent::ResetRotation()
{
	UnitCharacter->SetActorRotation(StartingTransform.GetRotation());
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Turn Ended")));
			EndUnitTurn();
		}, 1.0f, false);
}

