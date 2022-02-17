
#include "HealthComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Toontanks/GameModes/TankGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	GameModeRef = Cast<ATankGameModeBase>(GetWorld()->GetAuthGameMode());
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("%s is the Damaged Actor. %s is the Damage Causer."), *DamagedActor->GetName(), *DamageCauser->GetName());
	if (Damage <= 0) return;
	CurrentHP = FMath::Clamp((CurrentHP - Damage), 0.0f, MaxHP);
	if (CurrentHP == 0)
	{
		GameModeRef->ActorDied(DamagedActor);
	}
}

