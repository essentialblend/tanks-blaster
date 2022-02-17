
#include "PawnTurret.h"
#include "ToonTanks/PawnTank.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
    PlayerTankRef = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    FTimerHandle FireTimer;
    GetWorldTimerManager().SetTimer(FireTimer, this, &APawnTurret::CheckFireCondition, FireRate, true);

}

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (!PlayerTankRef || DistToPlayer() > LookDistance)
    {
        return;
    }
    RotateTurret(PlayerTankRef->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
    if (!PlayerTankRef) return;
    if (DistToPlayer() <= LookDistance && PlayerTankRef->IsPlayerAlive())
    {
        HeavyFireAt();
    }
}

float APawnTurret::DistToPlayer()
{
    return FVector::Dist(PlayerTankRef->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
