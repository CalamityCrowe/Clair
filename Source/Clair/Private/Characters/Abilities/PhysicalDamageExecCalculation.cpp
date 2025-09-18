// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Abilities/PhysicalDamageExecCalculation.h"
#include "Characters/Abilities/ClairAbilitySystemComponent.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"

struct PhysicalDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack) // attacker stat
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength) // attacker stat
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense) // defender stat
	DECLARE_ATTRIBUTE_CAPTUREDEF(Level) // attacker stat 

	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage) // output damage

	PhysicalDamageStatics()
	{
		// Attacker's attack stat
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Attack, Source, true);
		// Attacker's Strength 
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Strength, Source, true);

		// Defender's Defence
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Defense, Target, true);
		// Attacker's Level
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Level, Source, true);

		// Output Damage
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Damage, Target, false);
	}
};

static const PhysicalDamageStatics& DamageStatics()
{
	static PhysicalDamageStatics DmgStatics;
	return DmgStatics;
}

UPhysicalDamageExecCalculation::UPhysicalDamageExecCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().AttackDef);
	RelevantAttributesToCapture.Add(DamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(DamageStatics().DefenseDef);
	RelevantAttributesToCapture.Add(DamageStatics().LevelDef);

	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UPhysicalDamageExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetOwnerActor() : nullptr;
	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetOwnerActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Attack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackDef, EvaluationParameters, Attack);
	Attack = FMath::Max(Attack, 0);

	float Strength = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().StrengthDef, EvaluationParameters, Strength);
	Strength = FMath::Max(Strength, 0);

	float Defense = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DefenseDef, EvaluationParameters, Defense);
	Defense = FMath::Max(Defense, 0);

	float Level = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LevelDef, EvaluationParameters, Level);
	Level = FMath::Max(Level, 1); // level should be at least 1

	float Damage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage);
	Damage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);

	// Basic Physical Damage Formula

	float BaseDamage = Attack - Defense;
	float Bonus = Strength + FMath::RandHelper(FMath::Floor((Level + Strength) / 8) + 1); 
	float TotalDamage = BaseDamage * Bonus; 

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageDef.AttributeToCapture, EGameplayModOp::Additive, TotalDamage));

	UClairAbilitySystemComponent* TargetASC = Cast<UClairAbilitySystemComponent>(TargetAbilitySystemComponent);
	if (TargetASC)
	{
		UClairAbilitySystemComponent* SourceASC = Cast<UClairAbilitySystemComponent>(SourceAbilitySystemComponent);
		TargetASC->RecieveDamage(SourceASC, TotalDamage, TotalDamage);
	}
}
