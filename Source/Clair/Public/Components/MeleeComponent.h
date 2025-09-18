// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffect.h"
#include "MeleeComponent.generated.h"

class AUnitBaseCharacter;

USTRUCT(BlueprintType)
struct FMeleeHitInfo 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName SocketName;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float HitRadius = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TObjectPtr<UAnimMontage> MeleeAttackMontage;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLAIR_API UMeleeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void HitDetect();

	UFUNCTION(BlueprintCallable, Category = "Melee")
	void Attack();

	UAnimMontage* GetCurrentMontage() const { return CurrentMontage; }

private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (AllowPrivateAccess = "true"))
	TArray<FMeleeHitInfo> MeleeHitInfo;

	AUnitBaseCharacter* OwnerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DamageEffect;
		
	TObjectPtr<UAnimMontage> CurrentMontage;
	float CurrentRadius; 
	FName CurrentSocket; 



};
