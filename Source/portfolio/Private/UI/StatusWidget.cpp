// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatusWidget.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Framework/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UStatusWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)
	{
		return false;
	}

	TextBlockTotalCoins->TextDelegate.BindUFunction(this, "SetTextBlockTotalCoins");
	TextBlockTotalLifes->TextDelegate.BindUFunction(this, "SetTextBlockTotalLifes");

	return true;
}

FText UStatusWidget::SetTextBlockTotalLifes()
{
	if (const UMyGameInstance* GameInstanse=Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		return FText::FromString(FString::FromInt(GameInstanse->TotalLifes));
	}
	return FText();
}

FText UStatusWidget::SetTextBlockTotalCoins()
{
	if (const UMyGameInstance* GameInstanse=Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		return FText::FromString(FString::FromInt(GameInstanse->TotalCoins));
	}

	return FText();
}
