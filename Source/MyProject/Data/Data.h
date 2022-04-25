// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

//Make sure the Display name should be as same as the InputEvent name in project setting
UENUM(BlueprintType)
enum class AbilityInputID : uint8
{
 // 0 None
 None UMETA(DisplayName = "None"),
 // 1 Confirm
 Confirm UMETA(DisplayName = "Confirm"),
 // 2 Cancel
 Cancel UMETA(DisplayName = "Cancel"),
 // 3 Jump
 Jump UMETA(DisplayName = "Jump"),
 // 4 Sprint
 Sprint UMETA(DisplayName = "Sprint"),
 // 5 Melee
 Melee UMETA(DisplayName = "Melee"),
 //6 Guard
 Guard UMETA(DisplayName = "Guard"),
 //7 Sheathe
 Sheathe UMETA(DisplayName = "Sheathe"),
 //8 Run
 Run UMETA(DisplayName = "Run")
};
