// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class ABallCharacter;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyGameModeBase();
	void GameClear();

	void KillPlayer(ABallCharacter* Player);

	void RestartGame();

	FTransform SpawnTransform;

	int32 TotalCoins=0;

	int32 AddCoin(const int32 CoinNumber);

protected:
	virtual void BeginPlay() override;

private:
	void RespawnPlayer();

	int32 Life = 3;
};
