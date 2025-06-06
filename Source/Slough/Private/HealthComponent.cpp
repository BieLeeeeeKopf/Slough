// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "AnimationComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage_Implementation(float Damage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTpyeClass, FHitResult Hit)
{
	if (!CanTakeDamage_Implementation(DamageCauser)) return;
	UAnimationComponent* CurrAnimComp = GetOwner()->GetComponentByClass<UAnimationComponent>();
	if (Damage < CurrentHealth) {
		//����
		CurrentHealth -= Damage;
		OnDamaged.Broadcast(CurrentHealth,DamageCauser, Hit);
		UE_LOG(LogTemp, Log, TEXT("currentHealth:%f"), CurrentHealth);
		if (CurrAnimComp) {
			CurrAnimComp->PlayDamageAnimMonTage(false);
		}
	}
	else {
		//����
		UE_LOG(LogTemp, Log, TEXT("Actor die"));
		OnDie.Broadcast(DamageCauser, Hit);
		if (CurrAnimComp) {
			CurrAnimComp->PlayDamageAnimMonTage(true);
		}
	}
}

/// <summary>
/// ͨ��Actor��tag�ж��˺��Ƿ�����ͬһ��Ӫ��ɵ�
/// </summary>
/// <param name="DamageCauser"></param>
/// <returns></returns>
bool UHealthComponent::CanTakeDamage_Implementation(AActor* DamageCauser)
{
	for(const FName & tagA : GetOwner()->Tags) {
		for (const FName& tagB : DamageCauser->Tags) {
			if (tagA == tagB) {
				UE_LOG(LogTemp, Log, TEXT("Can Not Take Damage"));
				return false;
			}
				
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Can Take Damage"));
	return true;
}

