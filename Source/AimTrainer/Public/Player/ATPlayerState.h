// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ATPlayerState.generated.h"


UCLASS()
class AIMTRAINER_API AATPlayerState : public APlayerState
{
	GENERATED_BODY()
public:

	int32 GetShotsFired() const{return ShotsFired;} 
	void AddShot(){++ShotsFired;}

	int32 GetKillsNum() const{return KillsNum;} 
	void AddKill(){++KillsNum;}

private:

	int32 KillsNum = 0;
	int32 ShotsFired = 0;
};
