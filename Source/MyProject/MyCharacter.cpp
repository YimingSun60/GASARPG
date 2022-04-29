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


	removeInputFromInputBufferTime = 1.0f;
	CharacterCommands.SetNum(2);
	
	CharacterCommands[0].name = "Command1";
	CharacterCommands[0].inputs.Add("B");
	CharacterCommands[0].hasUsedCommand = false;

	CharacterCommands[1].name = "Command2";
	CharacterCommands[1].inputs.Add("C");
	CharacterCommands[1].hasUsedCommand = false;
	
	hasUsedTempCommand = false;


	removeInputFromInputBuffer = 1.0f;
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


void AMyCharacter::AddInputToInputBuffer(FInputInfo _inputInfo)
{
	for(int i = 0; i < CommandKeys.Num(); ++i)
	{
	//if input valid
		if(_inputInfo.InputMame == CommandKeys[i].CommandName)
		{
			if(inputBuffer.Num()==2)
			{
				inputBuffer.RemoveAt(0);
				UE_LOG(LogTemp,Warning,TEXT("The character removed an input"));
			}
			inputBuffer.Add(_inputInfo);
			UE_LOG(LogTemp,Warning,TEXT("The character added an input"));
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("input buffer size %i"), inputBuffer.Num());
}


//Find sequence in a list of command and find out if we pressed these buttons
//If have, start command
void AMyCharacter::CheckInputBufferForCommand()
{
	int correctSequeceCounter = 0;
	TArray<FInputInfo> Temp;
	Temp.Empty();
	FCommand TempCommand;
	//Loop through Command Array, Check if input buffer matches the single command
	//If Match, Start the command
	//If Not Match, execute the first input in input buffer
	for(auto currentCommand : CharacterCommands)
	{
		//Store the single command that matches the first element of input buffer 
		if(currentCommand.inputs.Num() == 1 && currentCommand.inputs[0] == inputBuffer[0].InputMame)
		{
			TempCommand = currentCommand;
		}
		//Filter the command array
		if(inputBuffer.Num() == currentCommand.inputs.Num())
		{
			// compare command with input buffer
			for(int commandInput = 0; commandInput < currentCommand.inputs.Num(); ++commandInput)
			{
				if(inputBuffer[commandInput].InputMame == currentCommand.inputs[commandInput])
				{
					correctSequeceCounter++;
				}
			}
			if(correctSequeceCounter == currentCommand.inputs.Num())
			{
				StartCommand(currentCommand);
				break;
			}
			correctSequeceCounter = 0;
		}
	}
	if(correctSequeceCounter != 0 && correctSequeceCounter != inputBuffer.Num())
	{
		Temp.Add(inputBuffer[0]);
		inputBuffer = Temp;
		StartCommand(TempCommand);
	}
}

//直接pass command class可能更好
void AMyCharacter::StartCommand(FCommand Command)
{
	UE_LOG(LogTemp,Warning,TEXT("The character is using the command: %s."),*Command.name);
	Command.hasUsedCommand = true;
}





//Iterate through the array of abilities and register InputID to the ability system component
//So that ability system could grand ability when the InputID is triggered.
void AMyCharacter::AquareAbility()
{

	for(TSubclassOf<UGameplayAbilities>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
		FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID) , this));
	}
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AMyCharacter::BindInput()
{
	if(IsValid(AbilitySystemComponent)&& IsValid(InputComponent))
	{
		
		//check(GEngine != nullptr);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Binding Success"));
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
		//PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::RunActive);
		//PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::RunInactive);
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

/*
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
*/

void AMyCharacter::WalkActive()
{
	Movementcomp->MaxWalkSpeed = 230;
}

void AMyCharacter::WalkInactive()
{
	Movementcomp->MaxWalkSpeed = 480;
}

void AMyCharacter::AccessInputBuffer()
{
	
}


