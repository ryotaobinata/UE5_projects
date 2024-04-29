// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;

private:

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlockTotalLifes;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlockTotalCoins;

	UFUNCTION()
	FText SetTextBlockTotalLifes();

	UFUNCTION()
	FText SetTextBlockTotalCoins();
};
