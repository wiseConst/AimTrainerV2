// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGameInstance.h"

const FGameData* UATGameInstance::GetCurrentGameData() const
{
	const FGameData* CurrentGameData = LevelsData.FindByPredicate(
		[&](const FGameData& LevelData)
		{
			return GetCurrentLevelName() == LevelData.LevelName;
		});
	return CurrentGameData;
}