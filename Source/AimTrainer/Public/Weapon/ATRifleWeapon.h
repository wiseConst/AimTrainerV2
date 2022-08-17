// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ATBaseWeapon.h"
#include "ATRifleWeapon.generated.h"

UCLASS()
class AIMTRAINER_API AATRifleWeapon : public AATBaseWeapon
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "0.001", ClampMax = "2.0"))
	float FireRate = 0.5f; 

	virtual void StartFire() override;
	virtual void StopFire() override;

private:
	
	FTimerHandle FireTimerHandle;
	virtual void MakeHit(const FHitResult& Hit) override;
};
