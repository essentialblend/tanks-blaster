
#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Toontanks/ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsComp;
	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMeshComp->SetupAttachment(CapsComp);
	TurretMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComp->SetupAttachment(BaseMeshComp);
	ProjSpawnComp = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjSpawnComp->SetupAttachment(TurretMeshComp);
}

void APawnBase::RotateTurret(FVector LookAtTarget) const
{
	const FRotator TurretRotation = FVector(FVector(LookAtTarget.X, LookAtTarget.Y, TurretMeshComp->GetComponentLocation().Z) - TurretMeshComp->GetComponentLocation()).Rotation();
	TurretMeshComp->SetWorldRotation(TurretRotation);
}

void APawnBase::HeavyFireAt()
{
	if (ProjectileClassRef)
	{
		AProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClassRef, ProjSpawnComp->GetComponentLocation(), ProjSpawnComp->GetComponentRotation());
		SpawnedProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CamShakeClassRef);
	UGameplayStatics::SpawnEmitterAtLocation(this, ParticleClassRef, GetActorLocation());
	
}

