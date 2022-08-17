// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ATPlayerController.generated.h"

UCLASS()
class AIMTRAINER_API AATPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	void OnTogglePauseMenu();
};
