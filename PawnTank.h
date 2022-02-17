// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerControllerBase;
class ALightProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
    USpringArmComponent* SpringArmComp = nullptr;
    UPROPERTY(EditAnywhere)
    UCameraComponent* CameraComp = nullptr;
    UPROPERTY(EditAnywhere, Category = "Tank Movement")
    float MoveSpeed{ 500.0f };
    UPROPERTY(EditAnywhere, Category = "Tank Movement")
    float RotateSpeed{ 500.0f };
    APlayerController* PlayerControllerRef = nullptr;
    UPROPERTY(EditAnywhere, Category = "Fire Rate")
    float HeavyFireRate{ 0.1f };
    UPROPERTY(EditAnywhere, Category = "Fire Rate")
    float LightFireRate{ 0.5f };
    FVector MoveDir{ 0,0,0 };
    FQuat RotateDirQ;
    UPROPERTY(EditAnywhere)
    TSubclassOf<ALightProjectileBase> LightProjectileClassRef;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UHealthComponent* HealthComponent = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    float TankMaxHP{ 0 };
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    float TankCurrentHP{ TankMaxHP };
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    float HPUIRate{0.0f};

    bool IsHeavyFireReady{ true };
    bool IsPlayerTankAlive{ true };
    void CalculateMoveDirection(float Value);
    void CalculateRotDirection(float Value);
    void MoveTank();
    void RotateTank();
    void SetHeavyFireCooldownState(bool IsCooldownOver);
    void StartLightFireAt();
    void StopLightFireAt();
    void LightFireAt();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void HeavyFireAt() override;
 

public:
    APawnTank();
    FTimerHandle LightFireTimer;
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    UFUNCTION(BlueprintCallable, Category = "Components")
    bool IsPlayerAlive() const;
    UFUNCTION()
    virtual void HandleDestruction() override;
    FTimerHandle LightCooldownTimer;
	
};
