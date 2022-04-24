// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasicAttribueSet.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float Health;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float HealthGeogenRate;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float Mana;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float MaxMana;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float ManaGeogenRate;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float Stamina;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float MaxStamina;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
	float StaminaGeogenRate;

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	virtual void GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	virtual void GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	virtual void GetStamina();

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	virtual void GetMaxStamina();
	
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	virtual float GetPercentStamina();
private:
	UBasicAttribueSet * AttributesSet;
	
};
