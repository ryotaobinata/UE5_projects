// Fill out your copyright notice in the Description page of Project Settings.


#include "GameElements/ItemCoin.h"
#include "Framework/MyGameModeBase.h"
#include "Framework/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

AItemCoin::AItemCoin()
{
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Assets/StaticMesh/S_CoinMesh"));
	ItemMesh->SetStaticMesh(Mesh);
}

void AItemCoin::GetItem()
{
	if (AMyGameModeBase* GameMode=Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		UMyGameInstance* GameInstanse = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		GameMode->AddCoin(Number);
		UE_LOG(LogTemp, Display, TEXT("TotalCoins:%d"), GameInstanse->TotalCoins);
	}
}
