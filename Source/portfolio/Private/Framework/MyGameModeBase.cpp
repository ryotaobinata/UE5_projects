// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MyGameModeBase.h"
#include "portfolio/BallCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Framework/MyGameInstance.h"
#include "Framework/InGameHUD.h"
#include "Framework/InGamePlayerController.h"

AMyGameModeBase::AMyGameModeBase() {
	DefaultPawnClass = ABallCharacter::StaticClass();
	HUDClass = AInGameHUD::StaticClass();
	PlayerControllerClass = AInGamePlayerController::StaticClass();
}

void AMyGameModeBase::GameClear()
{
	UE_LOG(LogTemp, Warning, TEXT("Congratulations! You have cleared the game!"));
}

void AMyGameModeBase::KillPlayer(ABallCharacter* Player)
{
	UMyGameInstance* GameInstanse = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Player->Destroy();
	GameInstanse->TotalLifes--;

	UE_LOG(LogTemp, Display, TEXT("TotalLifes:%d"), GameInstanse->TotalLifes);

	if (GameInstanse->TotalLifes>=0)
	{
		RespawnPlayer();
	}
	else
	{
		RestartGame();
	}
	
}

void AMyGameModeBase::RestartGame()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);

	AInGameHUD* HUD = Cast<AInGameHUD>(PlayerController->GetHUD());

	HUD->DispGameOver();
}

int32 AMyGameModeBase::AddCoin(const int32 CoinNumber)
{
	UMyGameInstance* GameInstanse = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanse->TotalCoins = GameInstanse->TotalCoins + CoinNumber;
	return GameInstanse->TotalCoins;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Viewportに配置されてたPlayerStartを探す
	const APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
	
	//PlayerStartの位置情報をリスポーンの位置として保持する
	SpawnTransform = PlayerStart->GetActorTransform();
}

void AMyGameModeBase::RespawnPlayer()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ABallCharacter* Player = GetWorld()->SpawnActor<ABallCharacter>(ABallCharacter::StaticClass(), SpawnTransform, SpawnInfo);

	//PlayerControllerの設定
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(Player);

}
