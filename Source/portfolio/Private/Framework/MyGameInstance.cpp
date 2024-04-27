// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MyGameInstance.h"

void UMyGameInstance::Initialize()
{
	//‰Šú’l‚ğ‚Â“¯‚¶ƒNƒ‰ƒX‚ÌDefaultObject‚ğæ“¾‚·‚é
	const UMyGameInstance* DefaultObject = GetDefault<UMyGameInstance>();

	this->TotalCoins = DefaultObject->TotalCoins;
	this->TotalLifes = DefaultObject->TotalLifes;
}
