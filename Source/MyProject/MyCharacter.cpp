// Fill out your copyright notice in the Description page of Project Settings.
#include "MyCharacter.h"
#include "Data/Data.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Full;
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TurnRateGamepad = 50.0f;
	Movementcomp = GetCharacterMovement();
	Movementcomp->MaxWalkSpeed = 480.0f;
	Movementcomp->bUseControllerDesiredRotation = true;
	Movementcomp->bOrientRotationToMovement = false;
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	BasicAttributes = CreateDefaultSubobject<UBasicAttribueSet>(TEXT("BasicAttributeSet"));
}

UAbilitySystemComponent* AMyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AquareAbility();
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

FGameplayTagContainer AMyCharacter::AddGameplayTags(FGameplayTagContainer Tag)
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->AddLooseGameplayTags(Tag);
	}
	return Tag;
}

FGameplayTagContainer AMyCharacter::RemoveGameplayTags(FGameplayTagContainer Tag)
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveLooseGameplayTags(Tag);
	}
	return Tag;
}

//Add ability and bind to the key
void AMyCharacter::AquareAbility()
{
	for(TSubclassOf<UGameplayAbilities>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
		FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID) , this));
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Aquare %hhd"), StartupAbility.GetDefaultObject()->AbilityInputID));
	}
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AMyCharacter::BindInput()
{
	if(IsValid(AbilitySystemComponent)&& IsValid(InputComponent))
	{
		
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Binding Success"));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("Comfirm"),
			FString("Cancel"), FString("AbilityInputID"), static_cast<int32>(AbilityInputID::Confirm), static_cast<int32>(AbilityInputID::Cancel)));

	}
}


// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	if(InputComponent)
	{
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));

		PlayerInputComponent->BindAxis("Move Forward / Backward",this,&AMyCharacter::MoveForward);
		PlayerInputComponent->BindAxis("Move Right / Left",this,&AMyCharacter::MoveRight);
		PlayerInputComponent->BindAxis("Turn Right / Left Mouse",this,&AMyCharacter::Turn);
		PlayerInputComponent->BindAxis("Look Up / Down Mouse",this,&AMyCharacter::Look);
		PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::RunActive);
		PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::RunInactive);
		PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AMyCharacter::WalkActive);
		PlayerInputComponent->BindAction("Walk", IE_Released, this, &AMyCharacter::WalkInactive);

		//Ability
		BindInput();
	}

}



void AMyCharacter::MoveForward(float Value)
{

	// find out which way is right
    	const FRotator Rotation = Controller->GetControlRotation();
    	const FRotator YawRotation(0, Rotation.Yaw, 0);
    	
    	// get right vector 
    	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Direction is : %f, %f"),Direction.X, Direction.Y));
    	// add movement in that direction
    	AddMovementInput(Direction, Value);
}

void AMyCharacter::MoveRight(float Value)
{
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Direction is : %f, %f"),Direction.X, Direction.Y));
	// add movement in that direction
	AddMovementInput(Direction, Value);

}

void AMyCharacter::Turn(float Value)
{
	AddControllerYawInput(Value * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::Look(float Value)
{
	AddControllerPitchInput(Value * TurnRateGamepad *GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::RunActive()
{
	Movementcomp->MaxWalkSpeed = 700;

	Movementcomp->bUseControllerDesiredRotation = false;
	Movementcomp->bOrientRotationToMovement = true;
}

void AMyCharacter::RunInactive()
{
	Movementcomp->MaxWalkSpeed = 480;

	Movementcomp->bUseControllerDesiredRotation = true;
	Movementcomp->bOrientRotationToMovement = false;
}

void AMyCharacter::WalkActive()
{
	Movementcomp->MaxWalkSpeed = 230;
}

void AMyCharacter::WalkInactive()
{
	Movementcomp->MaxWalkSpeed = 480;
}


