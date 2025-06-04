// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationComponent.h"

// Sets default values for this component's properties
UAnimationComponent::UAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	AnimBody = GetOwner()->FindComponentByTag<USkeletalMeshComponent>("Body");
	if (!AnimBody)
		UE_LOG(LogTemp, Log, TEXT("Not Find a AnimBody"));
	// ...
	
}


// Called every frame
void UAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UAnimationComponent::PlayDamageAnimMonTage_Implementation(bool isDied)
{
	if (!AnimBody) return;
	if (isDied) {
		AnimBody->GetAnimInstance()->Montage_Play(DamageAnim,1.0f);
	}
	else {
		AnimBody->GetAnimInstance()->Montage_Play(DieAnim, 1.0f);		
	}
	//绑定蒙太奇播放完成事件
	AnimBody->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &UAnimationComponent::OnDiedMontageEnded);
	AnimBody->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &UAnimationComponent::OnDiedMontageEnded);
}
/// <summary>
/// 蒙太奇播放完成回调函数
/// </summary>
/// <param name="Montage"></param>
/// <param name="bInterrupted"></param>
void UAnimationComponent::OnDiedMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Log, TEXT("Actor Dided"));
	AnimBody->SetCollisionEnabled(ECollisionEnabled::Type(3));
	AnimBody->SetSimulatePhysics(true);
	AnimBody->bPauseAnims = true;
}