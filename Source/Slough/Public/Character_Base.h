// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "AnimationComponent.h"
#include "Character_Base.generated.h"

UCLASS()
class SLOUGH_API ACharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// HealthComp
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	UHealthComponent* HealthComp;
	// AnimaComp
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")	
	UAnimationComponent* AnimaComp;
};
