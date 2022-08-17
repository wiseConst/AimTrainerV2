// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ATGameUserSettings.generated.h"

class UATGameSetting;

UCLASS()
class AIMTRAINER_API UATGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:

	UATGameUserSettings();

	static UATGameUserSettings* Get();

	const TArray<UATGameSetting*>& GetVideoSettings() const;

private:

	UPROPERTY()
	TArray<UATGameSetting*> VideoSettings;
};
