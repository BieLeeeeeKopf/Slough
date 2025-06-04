// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageInterface.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLOUGH_API UHealthComponent : public UActorComponent ,public IDamageInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float CurrentHealth;
	virtual void TakeDamage_Implementation(float Damage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTpyeClass)override;
};
