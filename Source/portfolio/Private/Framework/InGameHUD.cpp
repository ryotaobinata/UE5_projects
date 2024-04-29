// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/InGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Framework/MyGameInstance.h"

void AInGameHUD::BeginPlay()
{
	//WidgetBluePrint�̃N���X���擾
	FString StatusWidgetPath = TEXT("/Game/BluePrints/UI/BPW_Status.BPW_Status_C");
	TSubclassOf<UUserWidget> StatusWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*StatusWidgetPath)).LoadSynchronous();

	//WidgetBluePrint�̃N���X���擾
	FString PauseWidgetPath = TEXT("/Game/BluePrints/UI/BPW_Pause.BPW_Pause_C");
	TSubclassOf<UUserWidget> PauseWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*PauseWidgetPath)).LoadSynchronous();

	//WidgetBluePrint�̃N���X���擾
	FString GameOverWidgetPath = TEXT("/Game/BluePrints/UI/BPW_GameOver.BPW_GameOver_C");
	TSubclassOf<UUserWidget> GameOverWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*GameOverWidgetPath)).LoadSynchronous();

	//PlayerController�擾
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (StatusWidgetClass && PlayerController && PauseWidgetClass && GameOverWidgetClass)
	{
		UUserWidget* StatusWidget = UWidgetBlueprintLibrary::Create(GetWorld(), StatusWidgetClass, PlayerController);
		StatusWidget->AddToViewport(0);

		PauseWidget = UWidgetBlueprintLibrary::Create(GetWorld(), PauseWidgetClass, PlayerController);
		PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
		PauseWidget->AddToViewport(1);

		GameOverWidget = UWidgetBlueprintLibrary::Create(GetWorld(), GameOverWidgetClass, PlayerController);
		GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);
		GameOverWidget->AddToViewport(2);

	}
}

void AInGameHUD::DispPause(const bool IsPause)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (IsPause)
	{
		//Pause���j���[��\��
		PauseWidget->SetVisibility(ESlateVisibility::Visible);

		//UI���[�h�ɐݒ�
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, PauseWidget, EMouseLockMode::DoNotLock, false);

		//Game��Pause��Ԃɂ���
		UGameplayStatics::SetGamePaused(GetOwner(), true);

		//Mouse�J�[�\����\��
		PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		//Pause������
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		//Mouse�J�[�\�����\��
		PlayerController->SetShowMouseCursor(false);

		//Game��Input��Ԃ�߂�
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController, false);

		//Pause���j���[��܂��ݏ�Ԃɂ���
		PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AInGameHUD::OpenLevel(const FName LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void AInGameHUD::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayerController(), EQuitPreference::Quit, false);
}

void AInGameHUD::DispGameOver()
{
	GameOverWidget->SetVisibility(ESlateVisibility::Visible);

	APlayerController* PlayerController = GetOwningPlayerController();

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, GameOverWidget, EMouseLockMode::DoNotLock, false);

	UGameplayStatics::SetGamePaused(GetWorld(), true);

	PlayerController->SetShowMouseCursor(true);
}

void AInGameHUD::ContinueGame()
{
	UMyGameInstance* GameInstanse = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	GameInstanse->Initialize();

	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));

}
