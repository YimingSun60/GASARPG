// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MyCharacter.h"

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();
	DefaultPawnClass = AMyCharacter::StaticClass();
}
