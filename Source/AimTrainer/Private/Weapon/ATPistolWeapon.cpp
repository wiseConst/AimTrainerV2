// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/ATPistolWeapon.h"
#include "GameframeWork/Pawn.h"
#include "Enemy/BaseEnemyActor.h"
#include "Player/ATPlayerState.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void AATPistolWeapon::StartFire()
{
	MakeShot();
}

void AATPistolWeapon::StopFire()
{
	// NOTE: Do nothing because here's no timer firing.
}

void AATPistolWeapon::MakeHit(const FHitResult& Hit)
{
	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	const auto PlayerState = Pawn->GetPlayerState<AATPlayerState>();
	if (!PlayerState) return;

	PlayerState->AddShot();

	if (Hit.bBlockingHit && Hit.GetActor())
	{
		const auto EnemyActor = Cast<ABaseEnemyActor>(Hit.GetActor());
		if (!EnemyActor)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), MissedShotSound);
			return;
		}

		FVector RandomLocation = FVector(1800.0f, FMath::FRandRange(-1600, 1600), FMath::FRandRange(600, 3400));

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		auto SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemyActor>(EnemyActor->GetClass(), RandomLocation, FRotator::ZeroRotator, SpawnParams);
		while (!SpawnedEnemy)
		{
			RandomLocation = FVector(1800.0f, FMath::FRandRange(-1600, 1600), FMath::FRandRange(600, 3400));
			SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemyActor>(EnemyActor->GetClass(), RandomLocation, FRotator::ZeroRotator, SpawnParams);
		}

		EnemyActor->Destroy();

		// UE_LOG(LogTemp, Display, TEXT("Killed: %s"), *EnemyActor->GetName());

		PlayerState->AddKill();

		UGameplayStatics::PlaySound2D(GetWorld(), ImpactSound);
	}
}
