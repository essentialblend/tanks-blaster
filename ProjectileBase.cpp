// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Toontanks/PawnTurret.h"
#include "Toontanks/PawnTank.h"
#include "Toontanks/PawnBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMeshComp;
	ProjectileMeshComp->SetSimulatePhysics(true);
	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMeshComp->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	ProjectileMoveComp->InitialSpeed = ProjectileSpeed;
	ProjectileMoveComp->MaxSpeed = ProjectileSpeed + 200.0f;
	BulletTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Bullet Trails"));
	BulletTrail->SetupAttachment(RootComponent);
	InitialLifeSpan = 3.0f;
}

void AProjectileBase::BeginPlay()
{
    Super::BeginPlay();
	UGameplayStatics::SpawnSoundAtLocation(this, ProjectileSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileOwner = GetOwner();
	if (ProjectileOwner == nullptr) return;
	
	if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, GetOwner()->GetInstigatorController(), ProjectileOwner, DmgClassRef);
		if(AActor* TempActor = Cast<APawnBase>(OtherActor))
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, TempActor->GetActorLocation());
		}
		
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CamShakeRef);
	}
	Destroy();
}


