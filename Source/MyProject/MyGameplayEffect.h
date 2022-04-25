// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "MyGameplayEffect.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECT_API UMyGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	virtual FGameplayTagContainer AddGameplayTags(FGameplayTagContainer Tag);
	virtual FGameplayTagContainer RemoveGameplayTags(FGameplayTagContainer Tag);

private:
	UAbilitySystemComponent *AbilitySystemComponent;

};
