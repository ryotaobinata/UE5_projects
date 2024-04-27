// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"

void AMainMenuHUD::BeginPlay()
{
	//WidgetBluePrint���擾
	FString Path = TEXT("/Game/UI/MainMenu/BPW_MainMenu.BPW_MainMenu_C");
	TSubclassOf<UUserWidget> WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

	//PlayerController���擾
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//WidgetBluePrint��PlayerController���擾�o����������
	if (WidgetClass && PlayerController) {
		//Widget�̍쐬
		UUserWidget* UserWidget = UWidgetBlueprintLibrary::Create(GetWorld(), WidgetClass, PlayerController);

		//ViewPort�ɒǉ�
		UserWidget->AddToViewport(0);	//��O�ɒǉ�

		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, UserWidget, EMouseLockMode::DoNotLock, true, false);
		PlayerController->SetShowMouseCursor(true);
	}
}
