// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ATMenuWidget.generated.h"

class UButton;

UCLASS()
class AIMTRAINER_API UATMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelChoseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	virtual void NativeOnInitialized() override;

private:

	UFUNCTION()
	void OnStartPlay();

	UFUNCTION()
	void OnOpenSettings();

	UFUNCTION()
	void OnQuitGame();
};
