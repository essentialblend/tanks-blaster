// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APlayerControllerBase;
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	APawnTank* PlayerTank = nullptr;


protected:
	virtual void BeginPlay() override;
    UFUNCTION(BlueprintImplementableEvent)
    void GameStart();
    UFUNCTION(BlueprintImplementableEvent)
    void GameOver(bool DidPlayerWin);
	int32 NoOfTurrets{ 0 };
	

public:
	void ActorDied(AActor* DeadActor);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldTimerStart = false;
	APlayerControllerBase* PControllerRef = nullptr;
	UPROPERTY(EditAnywhere, Category = "Start Delay")
	float StartDelayTime{ 4.0f };
};
