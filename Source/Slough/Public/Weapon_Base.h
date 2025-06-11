// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon_Base.generated.h"

UCLASS()
class SLOUGH_API AWeapon_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
	int32 maxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
	int32 currentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
	int32 maxMagazineAmmunition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
	int32 currentMagazineAmmunition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName weaponSlot;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|FX")
	

};
