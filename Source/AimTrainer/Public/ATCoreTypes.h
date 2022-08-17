#pragma once

#include "ATCoreTypes.generated.h"

class ABaseEnemyActor;
class USoundMix;
class UImage;

// game

UENUM(BlueprintType)
enum class EGameModeData : uint8
{
	TileFrenzy = 0U,
	Tracking
};

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName LevelName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	EGameModeData GameModeData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	UTexture2D* LevelImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	TSubclassOf<ABaseEnemyActor> EnemyActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (EditCondition = "GameModeData != EGameModeData::Tracking", ClampMin = "1.0", ClampMax = "20.0"))
	int32 EnemyNum = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "15.0", ClampMax = "120.0"))
	float RoundTimeSeconds = 60.0f;
};

// weapon

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "50.0", ClampMax = "6000.0"))
	float MaxTraceDistance = 1500.0f;
};

// game mode

UENUM(BlueprintType)
enum class EATMatchState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Paused,
	GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChanged, EATMatchState);

// GAME SETTINGS

USTRUCT(BlueprintType)
struct FGameSettingsData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "10.0"))
	float SensitivityMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.00", ClampMax = "1.0"))
	float SoundVolume = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "30.00", ClampMax = "130.0"))
	float FOV = 90.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "10.0"))
	FColor TileFrenzyEnemyColor = FColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "10.0"))
	FColor TrackingEnemyColor = FColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	bool bShowGun = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	USoundMix* SoundMixMasterClass;
};