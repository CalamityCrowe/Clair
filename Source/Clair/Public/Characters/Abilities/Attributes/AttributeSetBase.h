// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h" 
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class CLAIR_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public: 
	UAttributeSetBase(); 

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Mana);

	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxMana);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Damage);

    // Speed
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData Speed;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, Speed);

    // Strength
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, Strength);

    // Magic
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData Magic;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, Magic);

    // Spirit
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData Spirit;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, Spirit);

    // Attack
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData Attack;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, Attack);

    // Defense
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, Defense);

    // Evade
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData Evade;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, Evade);

    // Magic Defense
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData MagDef;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, MagDef);

    // Magic Evasion
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    FGameplayAttributeData MagEva;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, MagEva);

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	FGameplayAttributeData ATBTick;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, ATBTick);

};
