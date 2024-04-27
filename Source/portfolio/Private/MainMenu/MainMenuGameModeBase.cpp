// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenuGameModeBase.h"
#include "MainMenu/MainMenuHUD.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	HUDClass = AMainMenuHUD::StaticClass();
}
