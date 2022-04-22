// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Ability/GameplayAbilities.h"
#include "AbilitySystemComponent.h"
#include "BasicAttribueSet.h"
#include "GameplayAbilitySpec.h"
#include "UObject/ObjectMacros.h"
#include "Abilities/GameplayAbility_CharacterJump.h"
#include "MyCharacter.generated.h"


UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	//Implement AbilitySystem Interface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//Bind the key input to the ability
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reference")
	UCharacterMovementComponent* Movementcomp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input axis
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void Look(float Value);

	//Input Action
	void RunActive();
	void RunInactive();
	void WalkActive();
	void WalkInactive();

	// Set AbilitySystem component
	UPROPERTY(BlueprintReadOnly, Category = "AbilitySytem")
	class UAbilitySystemComponent* AbilitySystemComponent;

	// Set SprintAbility
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilitySystem")
	TArray<TSubclassOf<class UGameplayAbilities>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere,Category = "AttributeSet")
	class UBasicAttribueSet* BasicAttributes;
	
	UFUNCTION(BlueprintCallable, Category = "GamePlayAbility")
	FGameplayTagContainer AddGameplayTags(const FGameplayTagContainer Tag);

	UFUNCTION(BlueprintCallable, Category = "GamePlayAbility")
	FGameplayTagContainer RemoveGameplayTags(const FGameplayTagContainer Tag);
	//Add Ability
	void AquareAbility();

	//Bind Input
	void BindInput();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
