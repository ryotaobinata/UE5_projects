// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/InGameHUD.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonContinue->OnClicked.AddUniqueDynamic(this, &UGameOverWidget::OnButtonContinueClicked);

	ButtonTitle->OnClicked.AddUniqueDynamic(this, &UGameOverWidget::OnButtonTitleClicked);

	ButtonQuit->OnClicked.AddUniqueDynamic(this, &UGameOverWidget::OnButtonQuitClicked);

}

void UGameOverWidget::OnButtonContinueClicked()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	AInGameHUD* HUD = Cast<AInGameHUD>(PlayerController->GetHUD());

	//ゲームをコンティニュー
	HUD->ContinueGame();
}

void UGameOverWidget::OnButtonTitleClicked()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	AInGameHUD* HUD = Cast<AInGameHUD>(PlayerController->GetHUD());

	HUD->OpenLevel(FName(TEXT("MainMenu")));

}

void UGameOverWidget::OnButtonQuitClicked()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	AInGameHUD* HUD = Cast<AInGameHUD>(PlayerController->GetHUD());

	HUD->QuitGame();
}
