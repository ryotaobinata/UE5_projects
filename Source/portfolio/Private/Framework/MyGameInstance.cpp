// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MyGameInstance.h"

void UMyGameInstance::Initialize()
{
	//�����l���������N���X��DefaultObject���擾����
	const UMyGameInstance* DefaultObject = GetDefault<UMyGameInstance>();

	this->TotalCoins = DefaultObject->TotalCoins;
	this->TotalLifes = DefaultObject->TotalLifes;
}
