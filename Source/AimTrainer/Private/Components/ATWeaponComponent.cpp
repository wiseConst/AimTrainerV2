// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ATWeaponComponent.h"
#include "Player/ATPawn.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapon/ATBaseWeapon.h"
#include "Weapon/ATPistolWeapon.h"
#include "Weapon/ATRifleWeapon.h"
#include "ATGameInstance.h"

UATWeaponComponent::UATWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UATWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();

	check(CurrentWeapon);
}

void UATWeaponComponent::StartFire()
{
	if (bIsEndedMatch)
	{
		StopFire();
		return;
	}

	SecondsSinceLastShot = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	CurrentWeapon->StartFire();
}

void UATWeaponComponent::StopFire()
{
	CurrentWeapon->StopFire();
}

void UATWeaponComponent::WeaponSway(float Yaw, float Pitch)
{
	const float MaxSwayDegree = 2.5f;
	FRotator InitialRotation = ATPawn->GetSkeletalMesh()->GetRelativeRotation();
	FRotator FinalRotation = FRotator(MaxSwayDegree * Yaw, MaxSwayDegree * Pitch, MaxSwayDegree * Yaw);

	FRotator TargetRotation = FRotator(InitialRotation.Pitch - FinalRotation.Pitch, InitialRotation.Yaw + FinalRotation.Yaw, InitialRotation.Roll + FinalRotation.Roll);

	FRotator NewRotation = FMath::RInterpTo(InitialRotation, TargetRotation, GetWorld()->DeltaTimeSeconds, 3.0f);

	ATPawn->GetSkeletalMesh()->SetRelativeRotation(FRotator(			//
		FMath::Clamp(NewRotation.Pitch, -MaxSwayDegree, MaxSwayDegree), //
		FMath::Clamp(NewRotation.Yaw, -MaxSwayDegree, MaxSwayDegree),	//
		FMath::Clamp(NewRotation.Roll, -MaxSwayDegree, MaxSwayDegree)	//
		));
}

void UATWeaponComponent::SpawnWeapons()
{
	if (!GetWorld()) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const auto GameInstance = GetWorld()->GetGameInstance<UATGameInstance>();
	if (!GameInstance) return;

	const auto CurrentGameData = GameInstance->GetCurrentGameData();
	if (!CurrentGameData) return;

	const auto CurrentGameModeData = CurrentGameData->GameModeData;
	
	if (CurrentGameModeData == EGameModeData::Tracking)
	{
		const auto Weapon = GetWorld()->SpawnActor<AATBaseWeapon>(RifleWeaponClass, SpawnParams);
		if (!Weapon) return;

		ATPawn = Cast<AATPawn>(GetOwner());
		if (!ATPawn) return;

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		Weapon->AttachToComponent(ATPawn->GetSkeletalMesh(), AttachmentRules);
		const FVector WeaponLocation = Weapon->GetActorLocation();
		Weapon->SetActorLocation(FVector(WeaponLocation.X, WeaponLocation.Y-2.0f,WeaponLocation.Z-10.0f));
		Weapon->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
		CurrentWeapon = Weapon;

		return;
	}
	else if (CurrentGameModeData == EGameModeData::TileFrenzy)
	{
		const auto Weapon = GetWorld()->SpawnActor<AATBaseWeapon>(PistolWeaponClass, SpawnParams);
		if (!Weapon) return;

		ATPawn = Cast<AATPawn>(GetOwner());
		if (!ATPawn) return;

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		Weapon->AttachToComponent(ATPawn->GetSkeletalMesh(), AttachmentRules);
		Weapon->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
		CurrentWeapon = Weapon;
		
		return;
	}
}