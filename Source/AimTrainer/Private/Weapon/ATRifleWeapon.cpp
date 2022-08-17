// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/ATRifleWeapon.h"
#include "GameframeWork/Pawn.h"
#include "Player/ATPlayerState.h"
#include "Enemy/BaseEnemyActor.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void AATRifleWeapon::StartFire()
{
	MakeShot();
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ThisClass::MakeShot, FireRate, true);
}

void AATRifleWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void AATRifleWeapon::MakeHit(const FHitResult& Hit)
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
		// UE_LOG(LogTemp, Display, TEXT("Killed: %s"), *EnemyActor->GetName());

		PlayerState->AddKill();

		
		UGameplayStatics::PlaySound2D(GetWorld(), ImpactSound);
	}
}