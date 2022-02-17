// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class AProjectileBase;
class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsComp = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMeshComp = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMeshComp = nullptr;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> ProjectileClassRef;
    UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CamShakeClassRef;
    UPROPERTY(EditAnywhere, Category = "Particle System")
    UParticleSystem* ParticleClassRef = nullptr;

protected:

	void RotateTurret(FVector LookAtTarget) const;
	virtual void HeavyFireAt();
	

public:
    // Sets default values for this pawn's properties
    APawnBase();
    UPROPERTY(EditAnywhere)
    USceneComponent* ProjSpawnComp = nullptr;
	virtual void HandleDestruction();
	

};
