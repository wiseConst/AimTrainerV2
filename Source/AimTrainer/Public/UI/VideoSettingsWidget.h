// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VideoSettingsWidget.generated.h"

class UVerticalBox;
class USettingOptionWidget;

UCLASS()
class AIMTRAINER_API UVideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VideoSettingsContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<USettingOptionWidget> SettingOptionWidgetClass;

	virtual void NativeOnInitialized() override;
};
