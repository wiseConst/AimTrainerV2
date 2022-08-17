// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGameUserSettings.h"
#include "ATGameSetting.h"

#define BIND_SETTINGS_FUNC(FUNC) \
	[&](int32 Level)             \
	{                            \
		FUNC(Level);             \
		ApplySettings(false);    \
	}

UATGameUserSettings::UATGameUserSettings()
{
	const TArray<FSettingOption> VFXOptions = {{"Low", 0}, {"Medium", 1}, {"High", 2}, {"Epic", 3}};

	{
		auto* Setting = NewObject<UATGameSetting>();
		check(Setting);
		Setting->SetName("Anti-Aliasing");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&](){return GetAntiAliasingQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetAntiAliasingQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<UATGameSetting>();
		check(Setting);
		Setting->SetName("Textures");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&](){return GetTextureQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetTextureQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<UATGameSetting>();
		check(Setting);
		Setting->SetName("Global Illumination");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&](){return GetGlobalIlluminationQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetGlobalIlluminationQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<UATGameSetting>();
		check(Setting);
		Setting->SetName("Shadows");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&](){return GetShadowQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetShadowQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<UATGameSetting>();
		check(Setting);
		Setting->SetName("Post-Processing");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&](){return GetPostProcessingQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetPostProcessingQuality));
		VideoSettings.Add(Setting);
	}
}

UATGameUserSettings* UATGameUserSettings::Get()
{
	return GEngine ? Cast<UATGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const TArray<UATGameSetting*>& UATGameUserSettings::GetVideoSettings() const
{
	return VideoSettings;
}