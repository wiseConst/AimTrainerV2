// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ATBaseWeapon.h"
#include "ATPistolWeapon.generated.h"

/**
 * 
 */
UCLASS()
class AIMTRAINER_API AATPistolWeapon : public AATBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
	virtual void StopFire() override;

private:

	virtual void MakeHit(const FHitResult& Hit) override;
};
