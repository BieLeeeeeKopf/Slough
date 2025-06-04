// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLOUGH_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DamageAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DieAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	USkeletalMeshComponent* AnimBody;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void PlayDamageAnimMonTage(bool isDied);
	UFUNCTION()
	void OnDiedMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
