// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AbilityIDDefines.h"
#include "UnitBaseCharacter.generated.h"

class UCombatComponent;
class UClairAbilitySystemComponent;
class UAttributeSetBase;
class UGameplayEffect;

UCLASS(BlueprintType)
class CLAIR_API UCharacterConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	//TArray<TSubclassOf<UGASGameplayAbility>> DefaultAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributes;
};

UCLASS()
class CLAIR_API AUnitBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter")
	virtual int32 GetAbilityLevel(EGASAbilityInputID AbilityInputID) const;

	UFUNCTION(BlueprintPure)
	FText GetCharacterName() const { return CharacterName; }

	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetMana() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetMaxMana() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetStrength() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetMagic() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetDefense() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetMagDef() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetSpeed() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetATBTick() const;



	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "GAS|GASCharacter")
	virtual void FinishDying();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 
	UPROPERTY(EditDefaultsOnly,Category = "GAS")
	FText CharacterName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UClairAbilitySystemComponent> ASC;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAttributeSetBase> AttributeSetBase;

	FGameplayTag DeathTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Config")
	TObjectPtr<UCharacterConfig> CharacterConfig;


	virtual void AddCharacterAbilities();

	virtual void IntializeAttributes();

	virtual void SetHealth(float NewHealth);

	virtual void SetMana(float NewMana);


public:	

	void PlayAttackMontage();

	UCombatComponent* GetCombatComponent() const { return CombatComponent; }
private: 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCombatComponent> CombatComponent;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
