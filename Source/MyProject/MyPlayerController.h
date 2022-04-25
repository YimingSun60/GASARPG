// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyCharacter.h"

#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void CreateHUD();

	class UHUDWidget* GetHUD();
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UHUDWidget> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UHUDWidget* UIHUDWidget;
	
};
