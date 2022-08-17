// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingOptionWidget.generated.h"

class UTextBlock;
class UATGameSetting;
class UButton;

UCLASS()
class AIMTRAINER_API USettingOptionWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingDisplayName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingCurrentValueTextBlock;

	UPROPERTY(meta = (BindWidget))
	UButton* NextSettingButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PrevSettingButton;

	virtual void NativeOnInitialized() override;

private:

	TWeakObjectPtr<UATGameSetting> Setting;

	void Init(UATGameSetting* InSetting);
	void UpdateTexts();

	UFUNCTION()
	void OnNextSetting();

	UFUNCTION()
	void OnPrevSetting();

	friend class UVideoSettingsWidget;
};
