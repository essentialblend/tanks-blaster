// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ATankGameModeBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	
	ATankGameModeBase* GameModeRef = nullptr;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	
    // Sets default values for this component's properties
    UHealthComponent();
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health Component Properties", meta = (AllowPrivateAccess = "true"))
	float CurrentHP{ 0 };
    UPROPERTY(EditAnywhere, Category = "Health Component Properties")
	float MaxHP{ 100 };
		
};
