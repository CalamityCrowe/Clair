// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UnitBaseCharacter.h"
#include "Components/CombatComponent.h"
#include "Characters/Abilities/ClairAbilitySystemComponent.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
// Sets default values
AUnitBaseCharacter::AUnitBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	ASC = CreateDefaultSubobject<UClairAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSetBase = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBase"));

}

UAbilitySystemComponent* AUnitBaseCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

bool AUnitBaseCharacter::IsAlive() const
{
	return GetHealth() > 0;
}

int32 AUnitBaseCharacter::GetAbilityLevel(EGASAbilityInputID AbilityInputID) const
{
	return 1;
}

float AUnitBaseCharacter::GetHealth() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetHealth();
	}
	return 0.0f;
}

float AUnitBaseCharacter::GetMaxHealth() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMaxHealth();
	}
	return 0.0f;
}

float AUnitBaseCharacter::GetMana() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMana();
	}
	return 0.0f;
}

float AUnitBaseCharacter::GetMaxMana() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMaxMana();
	}
	return 0.0f;
}

float AUnitBaseCharacter::GetStrength() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetStrength();
	}
	return 0.0f;
}
float AUnitBaseCharacter::GetMagic() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMagic();
	}
	return 0.0f;
}
float AUnitBaseCharacter::GetDefence() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetDefence();
	}
	return 0.0f;
}
float AUnitBaseCharacter::GetMagDefence() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMagDefence();
	}
	return 0.0f;
}
float AUnitBaseCharacter::GetAgility() const
{
	if (AttributeSetBase)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Agility: %f"), AttributeSetBase->GetAgility()));
		return AttributeSetBase->GetAgility();
	}
	return 0.0f;
}


void AUnitBaseCharacter::Die()
{
	if (ASC)
	{
		ASC->CancelAbilities();
	}
}

void AUnitBaseCharacter::FinishDying()
{
}

// Called when the game starts or when spawned
void AUnitBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ASC) 
	{
		ASC->InitAbilityActorInfo(this, this);
		IntializeAttributes(); 
		SetHealth(GetMaxHealth());
		SetMana(GetMaxMana());
	}

	// want to check if it has an anim instance and store it
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance()) 
	{
		AnimInstance->OnMontageBlendingOut.AddDynamic(this, &AUnitBaseCharacter::OnAttackMontageEnded);
	}
	
}

void AUnitBaseCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !ASC)
	{
		return;
	}

	// loops through all the abilities in the character config and gives them to the ASC if they are valid
	//for (TSubclassOf<UClairGameplayAbility> Ability : CharacterConfig->DefaultAbilities)
	//{
	//	if (Ability)
	//	{
	//		FGameplayAbilitySpec AbilitySpec(Ability, GetAbilityLevel(Ability.GetDefaultObject()->AbilityID), static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this);
	//		ASC->GiveAbility(AbilitySpec);
	//	}
	//}

	ASC->bCharacterAbilitiesGiven = true; // tells the ASC that it has recieved the abilities
}

void AUnitBaseCharacter::IntializeAttributes()
{
	if (!ASC)
	{
		return;
	}
	
	if (CharacterConfig->DefaultAttributes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultAttributes is not set for %s"), *GetName());
		return;
	}
	// we make an effect contect and tell it what actor to affect, in this case itself
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	// we loop through all the default attributes in the character config and apply them to the ASC based on the effect context handle
	for (TSubclassOf<UGameplayEffect>& DefaultAttribute : CharacterConfig->DefaultAttributes)
	{
		if (DefaultAttribute)
		{
			FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(DefaultAttribute, 1, EffectContext);
			if (EffectSpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}

void AUnitBaseCharacter::SetHealth(float NewHealth)
{
	if (AttributeSetBase)
	{
		AttributeSetBase->SetHealth(NewHealth);
	}
}

void AUnitBaseCharacter::SetMana(float NewMana)
{
	if (AttributeSetBase)
	{
		AttributeSetBase->SetMana(NewMana);
	}
}

void AUnitBaseCharacter::PlayAttackMontage()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
}

void AUnitBaseCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == AttackMontage)
	{
		CombatComponent->ReturnToStart();
	}
}


