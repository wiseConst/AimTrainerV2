// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ATPawn.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class UATWeaponComponent;
class USkeletalMeshComponent;

UCLASS()
class AIMTRAINER_API AATPawn : public APawn
{
	GENERATED_BODY()

public:

	AATPawn();

	USkeletalMeshComponent* GetSkeletalMesh() const {return SkeletalMeshComponent;}

	UFUNCTION(BlueprintCallable)
	const float& GetCurrentSensitivity() const {return Sensitivity;}

	UFUNCTION(BlueprintCallable)
	void SetCurrentSensitivity(float Sens){Sensitivity = Sens;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* FPPCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UATWeaponComponent* WeaponComponent;

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	float Sensitivity = 1.0f;

	float YawWeaponSway = 0.0f;
	float PitchWeaponSway = 0.0f;

	void TurnAround(float Amount);
	void LookUp(float Amount);
};
