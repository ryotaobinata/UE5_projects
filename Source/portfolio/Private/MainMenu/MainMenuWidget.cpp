// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonPlay->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonPlayClicked);
	ButtonQuit->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonQuitClicked);
}

void UMainMenuWidget::OnButtonPlayClicked()
{
	UMyGameInstance* GameInstanse = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanse->Initialize();

	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Level1")));
}

void UMainMenuWidget::OnButtonQuitClicked()
{
	if (APlayerController* PlayerController=UGameplayStatics::GetPlayerController(GetWorld(),0))
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}
