// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"
#include "Components/Button.h"
#include "GameframeWork/PlayerController.h"
#include "AimTrainer/AimTrainerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ATGameInstance.h"
#include "ATHUD.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &ThisClass::OnResume);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &ThisClass::OnRestartLevel);
	}

	if (OpenSettingsButton)
	{
		OpenSettingsButton->OnClicked.AddDynamic(this, &ThisClass::OnOpenSettings);
	}

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnGoToMenu);
	}
}

void UPauseWidget::OnResume()
{
	if (!GetWorld()) return;

	const auto PlayerController = GetOwningPlayer();
	if (!PlayerController) return;

	PlayerController->SetPause(!PlayerController->IsPaused());
	PlayerController->bShowMouseCursor = PlayerController->IsPaused();
	PlayerController->IsPaused() ? PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false)) : PlayerController->SetInputMode(FInputModeGameOnly());

	const auto GameMode = Cast<AAimTrainerGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->OnMatchStateChanged.Broadcast(EATMatchState::InProgress);
}

void UPauseWidget::OnRestartLevel()
{
	if (!GetWorld()) return;

	const FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld()));
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
}

void UPauseWidget::OnOpenSettings()
{
	const auto ATHUD = Cast<AATHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (!ATHUD) return;

	if (SettingsWidgetClass)
	{
		const auto SettingsWidget = CreateWidget<UUserWidget>(GetWorld(), SettingsWidgetClass);
		if (SettingsWidget)
		{
			SettingsWidget->AddToViewport();
		}
		ATHUD->InnerWidget = SettingsWidget;
	}
}

void UPauseWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<UATGameInstance>();
	if (!GameInstance) return;

	UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetMenuLevelName());
}