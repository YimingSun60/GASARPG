// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayEffect.h"


UMyGameplayEffect::UMyGameplayEffect()
{
}

FGameplayTagContainer UMyGameplayEffect::AddGamePlayTag(FGameplayTagContainer Tag)
{
	if(AbilitySystemComponent)
	{
		InheritableGameplayEffectTags.Added.AppendTags(Tag);
	}
	return Tag;
}
