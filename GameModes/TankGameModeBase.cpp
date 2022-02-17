// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Toontanks/PawnTank.h"
#include "Toontanks/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Toontanks/Controllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    PrimaryActorTick.bCanEverTick = true;
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    PControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    GameStart();

    TArray<AActor*> PawnTurretArray;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), PawnTurretArray);
    NoOfTurrets = PawnTurretArray.Num();
    UE_LOG(LogTemp, Warning, TEXT("Number of turrets: %d"), NoOfTurrets);

    if (PControllerRef)
    {
        PControllerRef->SetPlayerStateEnabled(false);
        FTimerHandle CursorAndHUDTimer;
        FTimerDelegate InputReEnable = FTimerDelegate::CreateUObject(PControllerRef, &APlayerControllerBase::SetPlayerStateEnabled, true);        
        GetWorldTimerManager().SetTimer(CursorAndHUDTimer, InputReEnable, StartDelayTime, false);
    }
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        GameOver(false);
        if (PControllerRef)
        {
            PControllerRef->SetPlayerStateEnabled(false);
        }
    }

    if (APawnTurret* DeadAct = Cast<APawnTurret>(DeadActor))
    {
        DeadAct->HandleDestruction();
        if (--NoOfTurrets <= 0)
        {
            GameOver(true);
        }
    }
}