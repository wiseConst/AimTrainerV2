// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ATBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameframeWork/Pawn.h"
#include "Player/ATPlayerState.h"


AATBaseWeapon::AATBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void AATBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void AATBaseWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector TraceStart;
	FVector TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	MakeHit(Hit);
}

void AATBaseWeapon::StartFire()
{
	MakeShot();
}

void AATBaseWeapon::StopFire()
{
}

bool AATBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return false;

	const auto Controller = Pawn->GetController<APlayerController>();
	if (!Controller) return false;

	FVector ViewLocation;
	FRotator ViewRotation;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const auto SocketTransform = WeaponMesh->GetSocketTransform(WeaponData.MuzzleSocketName);

	TraceStart = SocketTransform.GetLocation();
	TraceEnd = TraceStart + WeaponData.MaxTraceDistance * ViewRotation.Vector();
	return true;
}

void AATBaseWeapon::MakeHit(const FHitResult& Hit)
{
	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	const auto PlayerState = Pawn->GetPlayerState<AATPlayerState>();
	if (!PlayerState) return;

	PlayerState->AddShot();

	if (Hit.bBlockingHit && Hit.GetActor())
	{
		// WRITE HERE YOUR WEAPON LOGIC.

		// UE_LOG(LogTemp, Display, TEXT("Killed: %s"), *EnemyActor->GetName());

		PlayerState->AddKill();
	}
}