// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

void UMyUserWidget::GetHealth()
{
	Health = AttributesSet->GetHealth();
}

void UMyUserWidget::GetMaxHealth()
{
	MaxHealth = AttributesSet->GetMaxHealth();
}

void UMyUserWidget::GetStamina()
{
	Stamina = AttributesSet->GetStamina();
}

void UMyUserWidget::GetMaxStamina()
{
	MaxStamina = AttributesSet->GetMaxStamina();
}

float UMyUserWidget::GetPercentStamina()
{
	return AttributesSet->GetStamina()/AttributesSet->GetMaxStamina();
}




