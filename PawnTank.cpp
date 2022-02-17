// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Toontanks/LightProjectileBase.h"
#include "Toontanks/Components/HealthComponent.h"



APawnTank::APawnTank()
{
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
    SpringArmComp->SetupAttachment(RootComponent);
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    CameraComp->SetupAttachment(SpringArmComp);
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnTank::BeginPlay()
{
    Super::BeginPlay();
    PlayerControllerRef = Cast<APlayerController>(GetController());
    IsHeavyFireReady = true;
    IsPlayerTankAlive = true;
    TankCurrentHP = HealthComponent->MaxHP;
    
}

void APawnTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (TankCurrentHP > HealthComponent->CurrentHP)
    {
        TankCurrentHP -= DeltaTime * HPUIRate;
    }
    TankMaxHP = HealthComponent->MaxHP;

    RotateTank();
    MoveTank();
    
    if (PlayerControllerRef)
    {
        FHitResult RotateHit;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, RotateHit);
        RotateTurret(RotateHit.ImpactPoint);
    }
}

void APawnTank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveDirection);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotDirection);
    PlayerInputComponent->BindAction("FireHeavy", IE_Pressed, this, &APawnTank::HeavyFireAt);
    PlayerInputComponent->BindAction("FireLight", IE_Pressed, this, &APawnTank::StartLightFireAt);
    PlayerInputComponent->BindAction("FireLight", IE_Released, this, &APawnTank::StopLightFireAt);
}

void APawnTank::CalculateMoveDirection(float Value)
{
    MoveDir = FVector((Value * MoveSpeed * GetWorld()->DeltaTimeSeconds), 0, 0);
}

void APawnTank::CalculateRotDirection(float Value)
{
    float RotateDir = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator RotFR = FRotator(0, RotateDir, 0);
    RotateDirQ = FQuat(RotFR);
}

void APawnTank::MoveTank()
{
    AddActorLocalOffset(MoveDir, true);
}

void APawnTank::RotateTank() 
{
    AddActorLocalRotation(RotateDirQ, true);
}

 void APawnTank::SetHeavyFireCooldownState(bool IsCooldownOver)
{
     (IsCooldownOver) ? (IsHeavyFireReady = true) : (IsHeavyFireReady = false);
}

 void APawnTank::StartLightFireAt()
 {
     if(PlayerControllerRef->IsInputKeyDown(FKey("LeftMouseButton")))
     {
         GetWorldTimerManager().SetTimer(LightCooldownTimer, this, &APawnTank::LightFireAt, LightFireRate, true, 0.0f);
     }
     else
     {
         return;
     }
    
 }

 void APawnTank::StopLightFireAt()
 {
     GetWorldTimerManager().ClearTimer(LightCooldownTimer);
 }

void APawnTank::HeavyFireAt()
{
    UPROPERTY(BlueprintCallable)
    FTimerHandle HeavyCooldownTimer;
    if (IsHeavyFireReady)    
    {
        Super::HeavyFireAt();
        
        SetHeavyFireCooldownState(false);
        FTimerDelegate FireStateDelegate = FTimerDelegate::CreateUObject(this, &APawnTank::SetHeavyFireCooldownState, true);
        GetWorldTimerManager().SetTimer(HeavyCooldownTimer, FireStateDelegate, HeavyFireRate, false);
    }
    else
    {
        return;
    }
}

void APawnTank::LightFireAt()
{
    if (LightProjectileClassRef)
    {
        ALightProjectileBase* TempLightProjectile = GetWorld()->SpawnActor<ALightProjectileBase>(LightProjectileClassRef, ProjSpawnComp->GetComponentLocation(), ProjSpawnComp->GetComponentRotation());
        TempLightProjectile->SetOwner(this);
    }
}

void APawnTank::HandleDestruction()
{
    Super::HandleDestruction();
    IsPlayerTankAlive = false;
    SetActorHiddenInGame(true);
    FTimerHandle TickDisableTimer;
    FTimerDelegate TickDelegate = FTimerDelegate::CreateUObject(this, &AActor::SetActorTickEnabled, false);
    GetWorldTimerManager().SetTimer(TickDisableTimer, TickDelegate, 0.1f, false);
}

bool APawnTank::IsPlayerAlive() const
{
    return (IsPlayerTankAlive) ? true : false;
}
