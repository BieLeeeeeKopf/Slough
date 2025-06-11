// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BPI_PlayerInterface.h"
#include "PlayerStateEnum.h"
#include "Character_Player.generated.h"

UCLASS()
class SLOUGH_API ACharacter_Player : public ACharacter,public IBPI_PlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Player();
	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	/* Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

	/* MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	/* Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	/* Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	/* Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	/* Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* PauseAction;

	/* Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireAction;

	/* Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* AimAction;

	/* Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* CrouchAction;

	/* Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* SprintAction;

	/* StaticStep Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* StaticStepAction;


	/* Player State */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	EPlayerStateEnum PlayerCurrentStare;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	//MoveActionValue
	FVector2D IA_Move;
	
	//Action Event
	void MoveDown(const FInputActionValue& Value);
	void MoveUp(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void FireDown(const FInputActionValue& Value);
	void FireUp(const FInputActionValue& Value);
	void AimDown(const FInputActionValue& Value);
	void AimUp(const FInputActionValue& Value);
	void CrouchDown(const FInputActionValue& Value);
	void CrouchUp(const FInputActionValue& Value);
	void SprintDown(const FInputActionValue& Value);
	void SprintUp(const FInputActionValue& Value);
	void StaticStepDown(const FInputActionValue& Value);
	void StaticStepUp(const FInputActionValue& Value);


	UFUNCTION()
	void PauseDown(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/// <summary>
	/// 获取玩家瞄准偏移量
	/// </summary>
	/// <param name="HorizontalAngle">水平偏移量Yaw</param>
	/// <param name="VerticalAngle">垂直偏移量Pitch</param>
	void GetAimingOffset_Implementation(float& HorizontalAngle, float& VerticalAngle);
	/// <summary>
	/// 获取玩家移动输入量
	/// </summary>
	void GetMoveAction_Implementation(float& Forward, float& Right);
	/// <summary>
	/// 获取玩家移动速度及移动方向
	/// </summary>
	void GetSpeedAndDirection_Implementation(float& Speed, float& Direction);
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Player|Math")
	void ClampAimingOffset(float InValue, float& ReturnValue) const;
};

