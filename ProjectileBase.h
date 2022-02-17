// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UParticleSystem;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMeshComp = nullptr;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMoveComp = nullptr;
	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	float ProjectileSpeed{1000.0f};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Properties", meta = (AllowPrivateAccess = "true"))
	float ProjectileDamage{20.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* BulletTrail = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", meta = (AllowPrivateAccess = "true"))
    UParticleSystem* HitParticle = nullptr;
    UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DmgClassRef;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Projectile Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CamShakeRef = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Properties", meta = (AllowPrivateAccess = "true"))
	USoundBase* ProjectileSound = nullptr;

protected:
	virtual void BeginPlay() override;

public:
    // Sets default values for this actor's properties
    AProjectileBase();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
