// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UImage;
class AATPlayerState;
class UWidgetAnimation;

UCLASS()
class AIMTRAINER_API UPlayerHUDWidget : public UUserWidget
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
	UImage* CrosshairImage;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;

	virtual void NativeOnInitialized() override;
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

private:

	AATPlayerState* GetATPlayerState() const;

	void PlayDefaultAnimation();
};
