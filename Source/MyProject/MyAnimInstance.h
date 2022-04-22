// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Math/Vector.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	UMyAnimInstance();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
	bool isMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float direction;

	UFUNCTION(BlueprintCallable, Category = "Update Animation")
	void UpdateAnimationProperties();

	UFUNCTION(BlueprintCallable, Category = "Update Properties")
	void SetSpeed(APawn *Pawn);
	

	UFUNCTION(BlueprintCallable, Category = "Update Properties")
	void ShouldMove(APawn *Pawn);
	
};




