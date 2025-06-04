// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo_Base.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HealthComponent.h"
#include "DamageInterface.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AAmmo_Base::AAmmo_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // 创建碰撞组件
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
    CollisionComponent->OnComponentHit.AddDynamic(this, &AAmmo_Base::OnHit);
    RootComponent = CollisionComponent;

    // 创建可见网格组件
    BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
    BulletMesh->SetupAttachment(RootComponent);
    BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 创建移动组件
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = CollisionComponent;
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    InitialLifeSpan = 3.0f; // 子弹存在时间
}

// Called when the game starts or when spawned
void AAmmo_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmo_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmo_Base::OnHit_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!OtherActor) {
        Destroy();
        return;
    }

    //碰撞后播放对应材质的子弹碰撞声音
    UE_LOG(LogTemp, Log, TEXT("Hit Actor is: %s"), *OtherActor->GetName());

    //子弹造成伤害
    UHealthComponent* currHealth = OtherActor->FindComponentByClass<UHealthComponent>();
    if (!currHealth) {
        Destroy();
        UE_LOG(LogTemp, Log, TEXT("Hit Actor is Not Have HealthComponent"));
        return;
    }
    IDamageInterface::Execute_TakeDamage(currHealth, Damage, GetInstigatorController(), GetInstigator(), DamageType, Hit);
    Destroy();
}

