// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ATCoreTypes.h"
#include "ATGameInstance.generated.h"

UCLASS()
class AIMTRAINER_API UATGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	const TArray<FGameData>& GetLevelsData() const {return LevelsData;}

	const FName& GetCurrentLevelName() const{return CurrentLevelName;}
	void SetCurrentLevelName(const FName& LevelName){CurrentLevelName = LevelName;}

	const FGameSettingsData& GetGameSettingsData() const{return GameSettingsData;}

	const FGameData* GetCurrentGameData() const;

	const FName& GetMenuLevelName() const {return MenuLevelName;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting")
	FGameSettingsData GameSettingsData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels")
	TArray<FGameData> LevelsData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels")
	FName MenuLevelName = "MenuLevel";

private:

	UPROPERTY()
	FName CurrentLevelName = NAME_None;
};
