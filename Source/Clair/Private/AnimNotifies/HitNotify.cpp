// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/HitNotify.h"
#include "Characters/UnitBaseCharacter.h"
#include "Components/MeleeComponent.h"

UHitNotify::UHitNotify()
{

}

void UHitNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (AUnitBaseCharacter* CharRef = Cast<AUnitBaseCharacter>(MeshComp->GetOwner()))
	{
		if (CharRef->GetMeleeComponent())
		{
			CharRef->GetMeleeComponent()->HitDetect();
		}
	}
}
