// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ATCoreTypes.h"
#include "AimTrainerGameModeBase.generated.h"

UCLASS()
class AIMTRAINER_API AAimTrainerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	AAimTrainerGameModeBase();

	FOnMatchStateChanged OnMatchStateChanged;

protected:
		
	virtual void StartPlay() override;

private:

	EATMatchState CurrentMatchState = EATMatchState::WaitingToStart;

	FTimerHandle RoundCountDownTimer;
	float CurrentRoundTimeSeconds = 0.0f;

	void RoundTimerUpdate();

	void SpawnEnemies();

	void StartRound();

	void SetMatchState(EATMatchState MatchState);
};
