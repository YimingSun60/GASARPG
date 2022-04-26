// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include  "GameplayTags.h"
#include "MyGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()
private:
	UAbilitySystemComponent *AbilitySystemComponent;
public:
	UMyGameplayEffect();
	FGameplayTagContainer AddGamePlayTag(FGameplayTagContainer Tag);
};
