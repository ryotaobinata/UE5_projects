// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/InGamePlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Framework/InGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"

AInGamePlayerController::AInGamePlayerController()
{
	PauseAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/InputAction/IA_Pause"));
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent=Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AInGamePlayerController::DispPause);

	}
}

void AInGamePlayerController::BeginPlay()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this, false);

	SetShowMouseCursor(false);
}

void AInGamePlayerController::DispPause(const FInputActionValue& Value)
{
	if (const bool V=Value.Get<bool>())
	{
		if (AInGameHUD* GameHUD = Cast<AInGameHUD>(GetHUD())) {
			GameHUD->DispPause(!UGameplayStatics::IsGamePaused(GetWorld()));
		}
	}
}
