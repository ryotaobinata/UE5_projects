// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonExit;

	UPROPERTY(meta=(BindWidget))
	UButton* ButtonTitle;

	UPROPERTY(meta=(BindWidget))
	UButton* ButtonQuit;

	UFUNCTION()
	void OnButtonExitClicked();

	UFUNCTION()
	void OnButtonTitleClicked();

	UFUNCTION()
	void OnButtonQuitClicked();
};
