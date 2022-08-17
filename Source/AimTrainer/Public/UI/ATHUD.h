// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ATCoreTypes.h"
#include "ATHUD.generated.h"

UCLASS()
class AIMTRAINER_API AATHUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UPROPERTY()
	UUserWidget* InnerWidget = nullptr;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

private:

	UPROPERTY()
	TMap<EATMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;

	void OnMatchStateChanged(EATMatchState MatchState);
};
