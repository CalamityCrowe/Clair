// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Characters/UnitBaseCharacter.h"

UAttributeSetBase::UAttributeSetBase()
{
}

void UAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetMaxHealthAttribute()) 
	{
		if(NewValue < 0.0f)
		{
			NewValue = 0.0f;
		}
	}
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle EffectContext = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = EffectContext.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags); 

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	AUnitBaseCharacter* TargetCharacter = nullptr;

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<AUnitBaseCharacter>(TargetActor);
	}

	AActor* SourceActor = nullptr;
	AController* SourceController = nullptr;
	AUnitBaseCharacter* SourceCharacter = nullptr;

	// if the source is valid, we get the avatar actor and controller from the ability system component
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && SourceActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceActor))
			{
				SourceController = Pawn->GetController();
			}
		}
		if (SourceController)  // if the controller is valid , we get the character from the controller's pawn
		{
			SourceCharacter = Cast<AUnitBaseCharacter>(SourceController->GetPawn());
		}
		else
		{
			SourceCharacter = Cast<AUnitBaseCharacter>(SourceActor);
		}

		if (EffectContext.GetEffectCauser())
		{
			SourceActor = EffectContext.GetEffectCauser();
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		FHitResult HitResult;
		if (EffectContext.GetHitResult())
		{
			HitResult = *EffectContext.GetHitResult();
		}

		const float LocalDamage = GetDamage();
		SetDamage(0.0f);

		if (LocalDamage > 0.0f) 
		{
			bool WasAlive = true;

			if (TargetCharacter)
			{
				//WasAlive = TargetCharacter->IsAlive();
			}

			const float NewHealth = GetHealth() - LocalDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));

			if (TargetCharacter && WasAlive) 
			{
				
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
}
