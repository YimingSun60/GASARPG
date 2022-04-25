// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "BasicAttribueSet.h"
#include "MyProject/Ability/GameplayAbilities.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "StatusBarWidget.h"
#include "UHUDWidget.h"


AMyPlayerState::AMyPlayerState()
{
	
	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	AttributeSetBase = CreateDefaultSubobject<UBasicAttribueSet>(TEXT("AttributeSetBase"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;

	// Cache tags
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UBasicAttribueSet* AMyPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool AMyPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void AMyPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwner());
	if(PC)
	{
		UHUDWidget* HUD = PC->GetHUD();
		if(HUD)
		{
			HUD->ShowAbilityConfirmCancelText(ShowText);
		}
	}
}

float AMyPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float AMyPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float AMyPlayerState::GetHealthRegenRate() const
{
	return AttributeSetBase->GetHealthRegenRate();
}
float AMyPlayerState::GetStamina() const
{
	return AttributeSetBase->GetStamina();
}

float AMyPlayerState::GetMaxStamina() const
{
	return AttributeSetBase->GetMaxStamina();
}

float AMyPlayerState::GetStaminaRegenRate() const
{
	return AttributeSetBase->GetStaminaRegenRate();
}

/*
float AMyPlayerState::GetMana() const
{
	return AttributeSetBase->GetManna();
}

float AMyPlayerState::GetMaxMana() const
{
	return ...
}

float AMyPlayerState::GetHealthRegenRate() const
{
	return ...
}
*/

void AMyPlayerState::BeginPlay()
{
	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AMyPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &AMyPlayerState::MaxHealthChanged);
		HealthRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthRegenRateAttribute()).AddUObject(this, &AMyPlayerState::HealthRegenRateChanged);
/*
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaAttribute()).AddUObject(this, &AGDPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &AGDPlayerState::MaxManaChanged);
		ManaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaRegenRateAttribute()).AddUObject(this, &AGDPlayerState::ManaRegenRateChanged);
*/
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetStaminaAttribute()).AddUObject(this, &AMyPlayerState::StaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxStaminaAttribute()).AddUObject(this, &AMyPlayerState::MaxStaminaChanged);
		StaminaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetStaminaRegenRateAttribute()).AddUObject(this, &AMyPlayerState::StaminaRegenRateChanged);
/*
		XPChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetXPAttribute()).AddUObject(this, &AGDPlayerState::XPChanged);
		GoldChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetGoldAttribute()).AddUObject(this, &AGDPlayerState::GoldChanged);
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetCharacterLevelAttribute()).AddUObject(this, &AGDPlayerState::CharacterLevelChanged);
*/
		// Tag change callbacks
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AMyPlayerState::StunTagChanged);
	}
}




