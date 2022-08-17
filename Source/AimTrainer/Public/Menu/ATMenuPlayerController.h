// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ATMenuPlayerController.generated.h"


UCLASS()
class AIMTRAINER_API AATMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;
	
};
