// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElements/ItemBase.h"
#include "ItemCoin.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AItemCoin : public AItemBase
{
	GENERATED_BODY()
public:
	AItemCoin();
	
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 Number = 1;

	virtual void GetItem() override;
};
