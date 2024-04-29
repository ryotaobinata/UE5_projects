// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InGamePlayerController.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AInGamePlayerController();

	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

	void DispPause(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;
	
};
