// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/ATMenuPlayerController.h"

void AATMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly{});

	bShowMouseCursor = true;
}