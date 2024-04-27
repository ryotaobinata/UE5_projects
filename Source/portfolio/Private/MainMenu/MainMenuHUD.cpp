// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"

void AMainMenuHUD::BeginPlay()
{
	//WidgetBluePrint‚ðŽæ“¾
	FString Path = TEXT("/Game/UI/MainMenu/BPW_MainMenu.BPW_MainMenu_C");
	TSubclassOf<UUserWidget> WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

	//PlayerController‚ðŽæ“¾
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//WidgetBluePrint‚ÆPlayerController‚ªŽæ“¾o—ˆ‚½‚©”»’è
	if (WidgetClass && PlayerController) {
		//Widget‚Ìì¬
		UUserWidget* UserWidget = UWidgetBlueprintLibrary::Create(GetWorld(), WidgetClass, PlayerController);

		//ViewPort‚É’Ç‰Á
		UserWidget->AddToViewport(0);	//Žè‘O‚É’Ç‰Á

		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, UserWidget, EMouseLockMode::DoNotLock, true, false);
		PlayerController->SetShowMouseCursor(true);
	}
}
