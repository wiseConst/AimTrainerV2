// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ATHUD.h"
#include "Blueprint/UserWidget.h"
#include "AimTrainer/AimTrainerGameModeBase.h"

void AATHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EATMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EATMatchState::Paused, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EATMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for (const auto& GameWidgetPair : GameWidgets)
	{
		const auto OneGameWidget = GameWidgetPair.Value;
		if (OneGameWidget)
		{
			OneGameWidget->AddToViewport();
			OneGameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (GetWorld())
	{
		const auto ATGameMode = Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode());
		if (ATGameMode)
		{
			ATGameMode->OnMatchStateChanged.AddUObject(this, &AATHUD::OnMatchStateChanged);
		}
	}
}

void AATHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AATHUD::OnMatchStateChanged(EATMatchState MatchState)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (InnerWidget)
	{
		InnerWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(MatchState))
	{
		CurrentWidget = GameWidgets[MatchState];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}