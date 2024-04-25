// Fill out your copyright notice in the Description page of Project Settings.


#include "GameElements/ItemCoin.h"
#include "portfolio/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AItemCoin::AItemCoin()
{
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/EditorMeshes/EditorHelp"));
	ItemMesh->SetStaticMesh(Mesh);
}

void AItemCoin::GetItem()
{
	if (AMyGameModeBase* GameMode=Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->AddCoin(Number);
		UE_LOG(LogTemp, Display, TEXT("TotalNumber:%d"), GameMode->TotalCoins);
	}
}
