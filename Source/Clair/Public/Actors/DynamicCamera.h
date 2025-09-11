// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CameraInterface.h"
#include "DynamicCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CLAIR_API ADynamicCamera : public AActor, public ICameraInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetCameraLocation(AActor* ActorRef, const FVector NewLocation) override;

private: 
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector TargetLocation;

	FTimerHandle CameraHandle;

	void UpdateCameraLocation();
};
