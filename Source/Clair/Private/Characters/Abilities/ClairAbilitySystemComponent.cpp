// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Abilities/ClairAbilitySystemComponent.h"

void UClairAbilitySystemComponent::RecieveDamage(UClairAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	RecievedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
