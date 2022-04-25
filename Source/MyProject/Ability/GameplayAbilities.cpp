// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject\Ability\GameplayAbilities.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"

UGameplayAbilities::UGameplayAbilities()
{
	// Default to Instance Per Actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// Default tags that block this ability from activating
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")));
	
}

void UGameplayAbilities::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	if (ActivateAbilityOnGranted)
	{
		bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

FGameplayTagContainer UGameplayAbilities::AddTag(const FGameplayTagContainer Tag, UMyGameplayEffect *MyGameplayEffect)
{
	if(MyGameplayEffect)
	{
		MyGameplayEffect->AddGameplayTags(Tag);
	}
	
	return Tag;
}

FGameplayTagContainer UGameplayAbilities::RemoveTag(const FGameplayTagContainer Tag, UMyGameplayEffect *MyGameplayEffect)
{
	if(MyGameplayEffect)
	{
		MyGameplayEffect->RemoveGameplayTags(Tag);
	}
	
	return Tag;
}


