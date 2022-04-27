// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicAttribueSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MYPROJECT_API UBasicAttribueSet: public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UBasicAttribueSet();

	//AtributeSet Override
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, MaxHealth)
	// Health regen rate will passively increase Health every second
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData HealthRegenRate;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, HealthRegenRate)

	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, Damage)

	// Current stamina, used to execute special abilities. Capped by MaxStamina.
	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, Stamina)

	// MaxStamina is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, MaxStamina)

	// Stamina regen rate will passively increase Stamna every second
	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, StaminaRegenRate)

	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
	FGameplayAttributeData MANA;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, MANA)

	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
	FGameplayAttributeData MaxMANA;
	ATTRIBUTE_ACCESSORS(UBasicAttribueSet, MaxMANA)

protected:
	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);



};
