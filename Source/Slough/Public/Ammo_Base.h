// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo_Base.generated.h"

UCLASS()
class SLOUGH_API AAmmo_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// ��ײ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	class USphereComponent* CollisionComponent;

	// �ɼ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	class UStaticMeshComponent* BulletMesh;
	// �ƶ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	// �ӵ��˺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = "Damage")
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
