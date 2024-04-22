// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "BallCharacter.h"
AMyGameModeBase::AMyGameModeBase() {
	DefaultPawnClass = ABallCharacter::StaticClass();
}

void AMyGameModeBase::GameClear()
{
	UE_LOG(LogTemp, Warning, TEXT("Congratulations! You have cleared the game!"));
}
