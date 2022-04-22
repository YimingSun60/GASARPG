// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include <complex>
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	isMoving = false;
	speed = 0.0f;
	direction = 0.0f;
}

void UMyAnimInstance::UpdateAnimationProperties()
{
	APawn* Pawn = TryGetPawnOwner();
	ShouldMove(Pawn);
	SetSpeed(Pawn);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Direction is : %f"),direction));
}

void UMyAnimInstance::SetSpeed(APawn *Pawn)
{
	if(Pawn)
	{
		speed = Pawn->GetMovementComponent()->Velocity.Size();
	}
}



void UMyAnimInstance::ShouldMove(APawn* Pawn)
{
	if(Pawn)
	{
		if(Pawn->GetMovementComponent()->Velocity.Size()>0)
		{
			isMoving = true;
		}
		else
		{
			isMoving = false;
		}
	}
}


