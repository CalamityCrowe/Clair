// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DynamicCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADynamicCamera::ADynamicCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ADynamicCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADynamicCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADynamicCamera::SetCameraLocation(AActor* ActorRef, FVector NewLocation)
{
	if (ActorRef) 
	{
		FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
		AttachToActor(ActorRef, Rules);
	}
	else
	{
		TargetLocation = NewLocation;
		GetWorldTimerManager().SetTimer(CameraHandle, this, &ADynamicCamera::UpdateCameraLocation, 0.01f, true);
	}
}

void ADynamicCamera::UpdateCameraLocation()
{
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), 1));
	if (FVector::Dist(GetActorLocation(), TargetLocation) < 1)
	{
		GetWorldTimerManager().ClearTimer(CameraHandle);
	}
}
