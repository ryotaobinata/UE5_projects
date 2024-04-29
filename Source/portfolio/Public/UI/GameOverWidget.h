// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ButtonContinue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonTitle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonQuit;

	UFUNCTION()
	void OnButtonContinueClicked();

	UFUNCTION()
	void OnButtonTitleClicked();

	UFUNCTION()
	void OnButtonQuitClicked();

	
};
