// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Turret Properties")
	float LookDistance{400.0f};
	UPROPERTY(EditAnywhere, Category = "Turret Properties")
	float FireRate{ 2.0f };
	void CheckFireCondition();
	float DistToPlayer();
	APawnTank* PlayerTankRef = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
	

	
};
