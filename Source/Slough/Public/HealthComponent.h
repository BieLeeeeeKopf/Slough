// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageInterface.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDamagedSignature, float, DamageAmount, AActor*, DamageCauser, FHitResult, Hit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDieSignature, AActor*, DamageCauser, FHitResult, Hit);
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
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float CurrentHealth = 100.0f;
	virtual void TakeDamage_Implementation(float Damage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTpyeClass, FHitResult Hit)override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	bool CanTakeDamage(AActor* DamageCauser);

	// 受伤事件分发器（蓝图可绑定）
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDieSignature OnDie;
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDamagedSignature OnDamaged;
};
