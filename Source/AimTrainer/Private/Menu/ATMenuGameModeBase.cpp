// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/ATMenuGameModeBase.h"
#include "Menu/UI/ATMenuHUD.h"
#include "Menu/ATMenuPlayerController.h"

AATMenuGameModeBase::AATMenuGameModeBase()
{
	HUDClass = AATMenuHUD::StaticClass();
	PlayerControllerClass = AATMenuPlayerController::StaticClass();
}