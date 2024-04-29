// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/InGameHUD.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonExit->OnClicked.AddUniqueDynamic(this, &UPauseWidget::OnButtonExitClicked);

	ButtonQuit->OnClicked.AddUniqueDynamic(this, &UPauseWidget::OnButtonQuitClicked);

	ButtonTitle->OnClicked.AddUniqueDynamic(this, &UPauseWidget::OnButtonTitleClicked);
}

void UPauseWidget::OnButtonExitClicked()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	AInGameHUD* GameHUD = Cast<AInGameHUD>(PlayerController->GetHUD());

	GameHUD->DispPause(false);
}

void UPauseWidget::OnButtonTitleClicked()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	AInGameHUD* GameHUD = Cast<AInGameHUD>(PlayerController->GetHUD());

	GameHUD->OpenLevel(FName(TEXT("MainMenu")));
}

void UPauseWidget::OnButtonQuitClicked()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	AInGameHUD* GameHUD = Cast<AInGameHUD>(PlayerController->GetHUD());

	GameHUD->QuitGame();
}
