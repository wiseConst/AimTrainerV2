// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATCoreTypes.h"
#include "ATBaseWeapon.generated.h"

class USkeletalMeshComponent;
class USoundCue;

UCLASS()
class AIMTRAINER_API AATBaseWeapon : public AActor
{
	GENERATED_BODY()

public:

	AATBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FWeaponData WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	USoundCue* ImpactSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	USoundCue* MissedShotSound;

	virtual void BeginPlay() override;
	virtual void MakeHit(const FHitResult& Hit);
	void MakeShot();

private:

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);
};
