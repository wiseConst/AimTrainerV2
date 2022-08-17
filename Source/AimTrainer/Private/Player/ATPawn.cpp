// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ATPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ATWeaponComponent.h"
#include "ATGameInstance.h"

AATPawn::AATPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetCapsuleRadius(60.0f);
	CapsuleComponent->SetCapsuleHalfHeight(60.0f);

	FPPCamera = CreateDefaultSubobject<UCameraComponent>("FPPCamera");
	FPPCamera->SetupAttachment(GetRootComponent());
	FPPCamera->bUsePawnControlRotation = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMeshComponent->SetupAttachment(FPPCamera);

	WeaponComponent = CreateDefaultSubobject<UATWeaponComponent>("WeaponComponent");
}

void AATPawn::BeginPlay()
{
	Super::BeginPlay();

	if (const auto ATGameInstance = Cast<UATGameInstance>(GetGameInstance()))
	{
		Sensitivity = ATGameInstance->GetGameSettingsData().SensitivityMultiplier;
	}
}

void AATPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WeaponComponent->WeaponSway(PitchWeaponSway, YawWeaponSway); // NOTE: Changed sides to make it work.
}

void AATPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ThisClass::TurnAround);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, WeaponComponent, &UATWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, WeaponComponent, &UATWeaponComponent::StopFire);
}

void AATPawn::TurnAround(float Amount)
{
	YawWeaponSway = Amount;
	AddControllerYawInput(Amount * Sensitivity);
}

void AATPawn::LookUp(float Amount)
{
	PitchWeaponSway = Amount;
	AddControllerPitchInput(Amount * Sensitivity);
}