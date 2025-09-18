// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MeleeComponent.h"
#include "Characters/UnitBaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values for this component's properties
UMeleeComponent::UMeleeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMeleeComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<AUnitBaseCharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("MeleeComponent: Owner is not AUnitBaseCharacter"));
		return;
	}
	// ...
	
}

void UMeleeComponent::HitDetect()
{
	if (CurrentSocket.IsNone()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Socket Assigned"));
		return;
	}

	FVector Start = OwnerCharacter->GetMesh()->GetSocketLocation(CurrentSocket);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(OwnerCharacter);
	TArray<FHitResult> Hits;

	UKismetSystemLibrary::SphereTraceMultiForObjects(this, Start, Start, CurrentRadius, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, Hits, true);

#if WITH_EDITOR
	// Debug Sphere
	UKismetSystemLibrary::DrawDebugSphere(this, Start, CurrentRadius, 12, FLinearColor::Red, 2.0f, 1.0f);
#endif
	if (Hits.Num() > 0)
	{
		for (const FHitResult& Hit : Hits)
		{
			if (Hit.GetActor() && Hit.GetActor() != OwnerCharacter) 
			{
				if (AUnitBaseCharacter* HitCharacter = Cast<AUnitBaseCharacter>(Hit.GetActor()))
				{
					UAbilitySystemComponent* OwnerASC = OwnerCharacter->GetAbilitySystemComponent();
					UAbilitySystemComponent* HitASC = HitCharacter->GetAbilitySystemComponent();
					if (OwnerASC && HitASC && DamageEffect)
					{
						FGameplayEffectContextHandle EffectContext = OwnerASC->MakeEffectContext();
						EffectContext.AddSourceObject(OwnerCharacter);
						

						FGameplayEffectSpecHandle DamageSpecHandle = OwnerASC->MakeOutgoingSpec(DamageEffect, 0, EffectContext);
						HitASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
					}
				}	
			}
		}
	}

}

void UMeleeComponent::Attack()
{
	if(!OwnerCharacter || MeleeHitInfo.Num() < 1)
	{
		return;
	}
	UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}

	int Index = FMath::RandRange(0, MeleeHitInfo.Num() - 1);

	CurrentMontage = MeleeHitInfo[Index].MeleeAttackMontage;
	CurrentRadius = MeleeHitInfo[Index].HitRadius;
	CurrentSocket = MeleeHitInfo[Index].SocketName;

	AnimInstance->Montage_Play(CurrentMontage);
}


