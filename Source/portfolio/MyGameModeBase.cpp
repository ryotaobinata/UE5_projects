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
	RespawnPlayer();
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
