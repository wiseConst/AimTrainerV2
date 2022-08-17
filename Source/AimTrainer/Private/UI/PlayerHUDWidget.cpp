// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/PlayerHUDWidget.h"
#include "Player/ATPlayerState.h"

void UPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayDefaultAnimation();
}

void UPlayerHUDWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	if (InVisibility == ESlateVisibility::Visible)
	{
		PlayDefaultAnimation();
	}
}

void UPlayerHUDWidget::PlayDefaultAnimation()
{
	if (ShowAnimation)
	{
		PlayAnimation(ShowAnimation);
	}
}

int32 UPlayerHUDWidget::GetKillsNum() const
{
	const auto PlayerState = GetATPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UPlayerHUDWidget::GetShotsFired() const
{
	const auto PlayerState = GetATPlayerState();
	return PlayerState ? PlayerState->GetShotsFired() : 0;
}

float UPlayerHUDWidget::GetShotAccuracy() const
{
	const auto PlayerState = GetATPlayerState();

	return PlayerState && PlayerState->GetKillsNum() > 0 && PlayerState->GetShotsFired() > 0								//
			   ? static_cast<float>(PlayerState->GetKillsNum()) / static_cast<float>(PlayerState->GetShotsFired()) * 100.0f //
			   : 0.0f;
}

AATPlayerState* UPlayerHUDWidget::GetATPlayerState() const
{
	return GetOwningPlayerState() ? Cast<AATPlayerState>(GetOwningPlayerState()) : nullptr;
}