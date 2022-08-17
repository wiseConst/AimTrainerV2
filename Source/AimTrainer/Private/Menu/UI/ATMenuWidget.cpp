// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/UI/ATMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"

void UATMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UATMenuWidget::OnStartPlay);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UATMenuWidget::OnOpenSettings);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UATMenuWidget::OnQuitGame);
	}
}

void UATMenuWidget::OnStartPlay()
{
	if (!LevelChoseWidgetClass) return;

	const auto LevelChoseWidget = CreateWidget<UUserWidget>(GetWorld(), LevelChoseWidgetClass);

	if (LevelChoseWidget)
	{
		LevelChoseWidget->AddToViewport();
	}
}

void UATMenuWidget::OnOpenSettings()
{
	if (!SettingsWidgetClass) return;

	const auto SettingsWidget = CreateWidget<UUserWidget>(GetWorld(), SettingsWidgetClass);
	if (SettingsWidget)
	{
		SettingsWidget->AddToViewport();
	}
}

void UATMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}