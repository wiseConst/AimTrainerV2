// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ATWeaponComponent.generated.h"

class AATBaseWeapon;
class AATRifleWeapon;
class AATPistolWeapon;
class AATPawn;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AIMTRAINER_API UATWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UATWeaponComponent();

	void StartFire();
	void StopFire();

	void WeaponSway(float Yaw, float Pitch);

	UFUNCTION(BlueprintCallable)
	float GetSecondsSinceLastShot() const {return SecondsSinceLastShot;}

	UFUNCTION(BlueprintCallable)
	AATBaseWeapon* GetCurrentWeapon() const {return CurrentWeapon;}
	
	void SetMatchEnded(bool IsEnded){bIsEndedMatch = IsEnded;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AATPistolWeapon> PistolWeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AATRifleWeapon> RifleWeaponClass;


	virtual void BeginPlay() override;

private:
	bool bIsEndedMatch = false;

	UPROPERTY()
	AATPawn* ATPawn = nullptr;

	UPROPERTY()
	AATBaseWeapon* CurrentWeapon = nullptr;

	float SecondsSinceLastShot = -999.0f; // NOTE: If start value >=0 then in the beginning of game ControlRig anim will play.

	void SpawnWeapons();
};