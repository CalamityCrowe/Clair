// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HitNotify.generated.h"

/**
 * 
 */
UCLASS()
class CLAIR_API UHitNotify : public UAnimNotify
{
	GENERATED_BODY()
public: 
	UHitNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override
	{
		return FString("Hit Notify");
	}
};
