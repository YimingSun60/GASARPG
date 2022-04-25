// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Math/UnrealMathFPU.h"



FGameplayTagContainer UMyGameplayEffect::AddGameplayTags(FGameplayTagContainer Tag)
{
	if(AbilitySystemComponent)
	{
		InheritableGameplayEffectTags.Added.AppendTags(Tag);
	}
	return Tag;
}

FGameplayTagContainer UMyGameplayEffect::RemoveGameplayTags(FGameplayTagContainer Tag)
{
	if(AbilitySystemComponent)
	{
		InheritableGameplayEffectTags.Removed.AppendTags(Tag);
	}
	return Tag;
}
