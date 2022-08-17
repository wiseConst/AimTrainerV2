// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/EndGameWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ATPlayerState.h"

void UEndGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UEndGameWidget::OnRestartLevel);
	}

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UEndGameWidget::OnGoToMenu);
	}

	if (ShowAnimation)
	{
		PlayAnimation(ShowAnimation);
	}
}

void UEndGameWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	UGameplayStatics::OpenLevel(GetWorld(), MenuLevelName);
}

void UEndGameWidget::OnRestartLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

int32 UEndGameWidget::GetKillsNum() const
{
	const auto PlayerState = GetATPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UEndGameWidget::GetShotsFired() const
{
	const auto PlayerState = GetATPlayerState();
	return PlayerState ? PlayerState->GetShotsFired() : 0;
}

float UEndGameWidget::GetShotAccuracy() const
{
	const auto PlayerState = GetATPlayerState();

	return PlayerState && PlayerState->GetKillsNum() > 0 && PlayerState->GetShotsFired() > 0								//
			   ? static_cast<float>(PlayerState->GetKillsNum()) / static_cast<float>(PlayerState->GetShotsFired()) * 100.0f //
			   : 0.0f;
}

AATPlayerState* UEndGameWidget::GetATPlayerState() const
{
	return GetOwningPlayerState() ? Cast<AATPlayerState>(GetOwningPlayerState()) : nullptr;
}
