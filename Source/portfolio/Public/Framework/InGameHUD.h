// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	void DispPause(const bool IsPause);

	void OpenLevel(const FName LevelName);

	void QuitGame();

	void DispGameOver();

	void ContinueGame();
private:
	UUserWidget* PauseWidget;

	UUserWidget* GameOverWidget;
};
