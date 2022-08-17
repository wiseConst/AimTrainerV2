// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/UI/ChoseLevelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Spacer.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "Menu/UI/LevelItemWidget.h"
#include "ATGameInstance.h"

void UChoseLevelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitLevels();
}

void UChoseLevelWidget::InitLevels()
{
	if (!GetWorld() || !LevelHorizontalBox) return;

	const auto GameInstance = GetWorld()->GetGameInstance<UATGameInstance>();
	if (!GameInstance) return;

	LevelHorizontalBox->ClearChildren();

	for(const auto& Level : GameInstance->GetLevelsData())
	{
		auto LevelItem = CreateWidget<ULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if (!LevelItem) return;

		LevelItem->SetLevelTextBlockName(Level.LevelName);
		LevelItem->SetLevelImage(Level.LevelImage);
		LevelItem->OnAnimationStart.AddUObject(this, &UChoseLevelWidget::PlayLoadAnimation);
		OnAnimationFinished.AddUObject(LevelItem, &ULevelItemWidget::OnAnimationFinished);

		LevelHorizontalBox->AddChildToHorizontalBox(LevelItem);
	}
}

void UChoseLevelWidget::PlayLoadAnimation(ULevelItemWidget* UserWidget)
{
	if (!UserWidget || !UserWidget->bIsClicked) return;
	
	ChosenLevelWidget = UserWidget;
	if (LoadImage)
	{
		LoadImage->SetBrushFromTexture(ChosenLevelWidget->ImageTexture);
	}
	PlayAnimation(LoadingAnimation);
}

void UChoseLevelWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (LoadingAnimation != Animation || !ChosenLevelWidget || !ChosenLevelWidget->bIsClicked) return;

	OnAnimationFinished.Broadcast(ChosenLevelWidget);
}