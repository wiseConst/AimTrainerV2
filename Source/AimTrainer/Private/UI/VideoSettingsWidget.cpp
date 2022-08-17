// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VideoSettingsWidget.h"
#include "AimTrainer/Settings/ATGameUserSettings.h"
#include "Components/VerticalBox.h"
#include "UI/SettingOptionWidget.h"

void UVideoSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto* UserSettings = UATGameUserSettings::Get();
	if (!UserSettings) return;

	UserSettings->LoadSettings();
	const auto VideoSettings = UserSettings->GetVideoSettings();

	check(VideoSettingsContainer);
	VideoSettingsContainer->ClearChildren();

	for (auto* Setting : VideoSettings)
	{
		const auto SettingWidget = CreateWidget<USettingOptionWidget>(this, SettingOptionWidgetClass);
		check(SettingWidget);
		SettingWidget->Init(Setting);
		VideoSettingsContainer->AddChild(SettingWidget);
	}
}