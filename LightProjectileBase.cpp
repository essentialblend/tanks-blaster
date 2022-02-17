// Fill out your copyright notice in the Description page of Project Settings.


#include "LightProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALightProjectileBase::ALightProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LightProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Projectile Mesh"));
	RootComponent = LightProjectileMeshComponent;
	LightProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	LightProjHitTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle"));
	LightProjHitTrail->SetupAttachment(RootComponent);
	LightProjectileMovementComponent->InitialSpeed = LightProjMaxSpeed;
	LightProjectileMovementComponent->MaxSpeed = LightProjMaxSpeed;

	InitialLifeSpan = 2.5f;

	LightProjectileMeshComponent->OnComponentHit.AddDynamic(this, &ALightProjectileBase::OnHit);

}

void ALightProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    AActor* ProjectileOwner = GetOwner();
    if (ProjectileOwner == nullptr) return;

    if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner)
    {
        UGameplayStatics::ApplyDamage(OtherActor, LightProjectileDamage, GetOwner()->GetInstigatorController(), ProjectileOwner, DmgClassRef);
        UGameplayStatics::SpawnEmitterAtLocation(this, LightProjEnemyHitParticle, OtherActor->GetActorLocation());
    }

    Destroy();
}


