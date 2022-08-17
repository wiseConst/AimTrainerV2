// Copyright Epic Games, Inc. All Rights Reserved.

#include "AimTrainerGameModeBase.h"
#include "Player/ATPawn.h"
#include "Player/ATPlayerController.h"
#include "Player/ATPlayerState.h"
#include "UI/ATHUD.h"
#include "Enemy/BaseEnemyActor.h"
#include "ATGameInstance.h"
#include "Components/ATWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogATGameMode, All, All)

AAimTrainerGameModeBase::AAimTrainerGameModeBase()
{
	DefaultPawnClass = AATPawn::StaticClass();
	PlayerControllerClass = AATPlayerController::StaticClass();
	PlayerStateClass = AATPlayerState::StaticClass();
	HUDClass = AATHUD::StaticClass();
}

void AAimTrainerGameModeBase::StartPlay()
{
	Super::StartPlay();

	StartRound();
}

void AAimTrainerGameModeBase::SpawnEnemies()
{
	if (!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<UATGameInstance>();
	if (!GameInstance) return;

	const auto CurrentGameData = GameInstance->GetCurrentGameData();

	if (!CurrentGameData)
	{
		UE_LOG(LogATGameMode, Error, TEXT("Can't find current GameModeData"));
		return;
	}

	CurrentRoundTimeSeconds = CurrentGameData->RoundTimeSeconds;

	switch (CurrentGameData->GameModeData)
	{
		case EGameModeData::TileFrenzy:
		{

			UE_LOG(LogTemp, Display, TEXT("%s"), *UEnum::GetValueAsName(EGameModeData::TileFrenzy).ToString());

			for (int32 i = 0; i < CurrentGameData->EnemyNum; ++i)
			{
				FVector RandomLocation = FVector(1800.0f, FMath::FRandRange(-1600.0f, 1600.0f), FMath::FRandRange(600.0f, 3400.0f));

				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

				auto SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemyActor>(CurrentGameData->EnemyActorClass, RandomLocation, FRotator::ZeroRotator, SpawnParams);
				while (!SpawnedEnemy)
				{
					RandomLocation = FVector(1800.0f, FMath::FRandRange(-1600.0f, 1600.0f), FMath::FRandRange(600.0f, 3400.0f));
					SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemyActor>(CurrentGameData->EnemyActorClass, RandomLocation, FRotator::ZeroRotator, SpawnParams);
				}
				SpawnedEnemy->GetStaticMesh()->CreateAndSetMaterialInstanceDynamic(0)->SetVectorParameterValue(FName("BaseColor"), GameInstance->GetGameSettingsData().TileFrenzyEnemyColor);
			}

			break;
		}
		case EGameModeData::Tracking:
		{

			UE_LOG(LogTemp, Display, TEXT("%s"), *UEnum::GetValueAsName(EGameModeData::Tracking).ToString());

			FVector RandomLocation = FVector(1800.0f, FMath::FRandRange(-1600.0f, 1600.0f), 2250.0f);

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

			const auto SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemyActor>(CurrentGameData->EnemyActorClass, RandomLocation, FRotator::ZeroRotator, SpawnParams);
			if (!SpawnedEnemy)
			{
				UE_LOG(LogATGameMode, Error, TEXT("Can't spawn Enemy"));
				return;
			}

			SpawnedEnemy->GetStaticMesh()->CreateAndSetMaterialInstanceDynamic(0)->SetVectorParameterValue(FName("BaseColor"), GameInstance->GetGameSettingsData().TrackingEnemyColor);

			break;
		}
		default: UE_LOG(LogTemp, Display, TEXT("Default level.")); break;
	}
}

void AAimTrainerGameModeBase::RoundTimerUpdate()
{
	if (FMath::IsNearlyZero(--CurrentRoundTimeSeconds))
	{
		GetWorld()->GetTimerManager().ClearTimer(RoundCountDownTimer);

		const auto PlayerController = GetWorld()->GetFirstPlayerController();
		if (!PlayerController) return;

		PlayerController->GetPawn()->DisableInput(nullptr);
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeUIOnly{});
		SetMatchState(EATMatchState::GameOver);

		const auto WeaponComponent = Cast<UATWeaponComponent>(PlayerController->GetPawn()->GetComponentByClass(UATWeaponComponent::StaticClass()));
		if (!WeaponComponent) return;

		WeaponComponent->SetMatchEnded(true);
		WeaponComponent->StopFire();
	}
}

void AAimTrainerGameModeBase::StartRound()
{
	if (!GetWorld()) return;

	SetMatchState(EATMatchState::InProgress);
	SpawnEnemies();
	GetWorld()->GetTimerManager().SetTimer(RoundCountDownTimer, this, &AAimTrainerGameModeBase::RoundTimerUpdate, 1.0f, true);
}

void AAimTrainerGameModeBase::SetMatchState(EATMatchState MatchState)
{
	if (CurrentMatchState == MatchState) return;

	OnMatchStateChanged.Broadcast(MatchState);
}