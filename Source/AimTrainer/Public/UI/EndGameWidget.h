// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

class UButton;
class AATPlayerState;
class UWidgetAnimation;

UCLASS()
class AIMTRAINER_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetShotsFired() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetShotAccuracy() const;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* GoToMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FName MenuLevelName = "MenuLevel";

	virtual void NativeOnInitialized() override;

private:

	AATPlayerState* GetATPlayerState() const;

	UFUNCTION()
	void OnGoToMenu();

	UFUNCTION()
	void OnRestartLevel();
};
