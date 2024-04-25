// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "BallCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AMyGameModeBase::AMyGameModeBase() {
	DefaultPawnClass = ABallCharacter::StaticClass();
}

void AMyGameModeBase::GameClear()
{
	UE_LOG(LogTemp, Warning, TEXT("Congratulations! You have cleared the game!"));
}

void AMyGameModeBase::KillPlayer(ABallCharacter* Player)
{
	Player->Destroy();
	Life--;
	if (Life>=0)
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
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}

int32 AMyGameModeBase::AddCoin(const int32 CoinNumber)
{
	TotalCoins = TotalCoins + CoinNumber;
	return TotalCoins;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Viewport�ɔz�u����Ă�PlayerStart��T��
	const APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
	
	//PlayerStart�̈ʒu�������X�|�[���̈ʒu�Ƃ��ĕێ�����
	SpawnTransform = PlayerStart->GetActorTransform();
}

void AMyGameModeBase::RespawnPlayer()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ABallCharacter* Player = GetWorld()->SpawnActor<ABallCharacter>(ABallCharacter::StaticClass(), SpawnTransform, SpawnInfo);

	//PlayerController�̐ݒ�
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(Player);
}
