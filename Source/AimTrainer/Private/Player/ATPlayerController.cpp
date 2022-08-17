// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ATPlayerController.h"
#include "AimTrainer/AimTrainerGameModeBase.h"

void AATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly{});
}

void AATPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAction("ToggleMenu", EInputEvent::IE_Pressed, this, &ThisClass::OnTogglePauseMenu).bExecuteWhenPaused = true;
}

void AATPlayerController::OnTogglePauseMenu()
{
	if (!GetWorld()) return;

	SetPause(!IsPaused());
	bShowMouseCursor = IsPaused();
	IsPaused() ? SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false)) : SetInputMode(FInputModeGameOnly());

	const auto GameMode = Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	
	GameMode->OnMatchStateChanged.Broadcast(IsPaused() ? EATMatchState::Paused : EATMatchState::InProgress);
}