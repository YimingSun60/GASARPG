// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyProject\Data\Data.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "MyProject\MyGameplayEffect.h"
#include "GameplayAbilities.generated.h"
/**
 * 
 */
UCLASS()
class MYPROJECT_API UGameplayAbilities : public UGameplayAbility
{
	GENERATED_BODY()
private:
	UAbilitySystemComponent *AbilitySystemComponent;
	//UMyGameplayEffect * MyGameplayEffect;
public:
	UGameplayAbilities();
	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	AbilityInputID AbilityInputID = AbilityInputID::None;
	
	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UFUNCTION(BlueprintCallable)
	FGameplayTagContainer AddTag(const FGameplayTagContainer Tag, UMyGameplayEffect* MyGameplayEffect);

	UFUNCTION(BlueprintCallable)
	FGameplayTagContainer RemoveTag(const FGameplayTagContainer Tag, UMyGameplayEffect* MyGameplayEffect);
};
