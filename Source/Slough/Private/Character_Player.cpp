// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Player.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
ACharacter_Player::ACharacter_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void ACharacter_Player::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void ACharacter_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacter_Player::MoveDown);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACharacter_Player::MoveUp);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacter_Player::Look);

		//Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ACharacter_Player::PauseDown);

		//Fire
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ACharacter_Player::FireDown);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &ACharacter_Player::FireUp);

		//Aim
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ACharacter_Player::AimDown);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &ACharacter_Player::AimUp);

		//Crouch
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ACharacter_Player::CrouchDown);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &ACharacter_Player::CrouchUp);

		//Sprint
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ACharacter_Player::SprintDown);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &ACharacter_Player::SprintUp);

		//StaticStep
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ACharacter_Player::StaticStepDown);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &ACharacter_Player::StaticStepUp);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACharacter_Player::GetAimingOffset_Implementation(float& HorizontalAngle, float& VerticalAngle)
{	
	if (!Controller) return;
	//Set HorizontalAngle
	ClampAimingOffset(Controller->GetControlRotation().Yaw - GetActorRotation().Yaw, HorizontalAngle);
	//Set VerticalAngle
	ClampAimingOffset(Controller->GetControlRotation().Pitch - GetActorRotation().Pitch, VerticalAngle);
}

void ACharacter_Player::GetSpeedAndDirection_Implementation(float& Speed, float& Direction)
{
	Speed = GetVelocity().Length();
	Direction = FMath::Atan2(GetVelocity().Y, GetVelocity().X);
}

void ACharacter_Player::ClampAimingOffset(float InValue, float& ReturnValue) const
{
	if (InValue > 180.0) {
		ReturnValue = FMath::GetMappedRangeValueClamped(FVector2D(270.0, 360.0), FVector2D(-90.0, 0.0), InValue);
	}
	else {
		ReturnValue = FMath::Clamp(InValue, 0.0, 90.0);
	}
}

void ACharacter_Player::GetMoveAction_Implementation(float& Forward, float& Right)
{
	Forward = IA_Move.Y;
	Right = IA_Move.X;
}



void ACharacter_Player::MoveDown(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		IA_Move = MovementVector;
	}
}

void ACharacter_Player::MoveUp(const FInputActionValue& Value)
{
	IA_Move = FVector2D(0.f, 0.f);
}

void ACharacter_Player::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACharacter_Player::FireDown(const FInputActionValue& Value)
{

}

void ACharacter_Player::FireUp(const FInputActionValue& Value)
{

}

void ACharacter_Player::AimDown(const FInputActionValue& Value)
{

}

void ACharacter_Player::AimUp(const FInputActionValue& Value)
{

}

void ACharacter_Player::CrouchDown(const FInputActionValue& Value)
{

}

void ACharacter_Player::CrouchUp(const FInputActionValue& Value)
{

}

void ACharacter_Player::SprintDown(const FInputActionValue& Value)
{
}

void ACharacter_Player::SprintUp(const FInputActionValue& Value)
{
}

void ACharacter_Player::StaticStepDown(const FInputActionValue& Value)
{
}

void ACharacter_Player::StaticStepUp(const FInputActionValue& Value)
{
}

void ACharacter_Player::PauseDown(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Pause key Down!"));
}
