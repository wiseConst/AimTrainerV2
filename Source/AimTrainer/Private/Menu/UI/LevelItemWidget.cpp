// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/UI/LevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "ATGameInstance.h"

void ULevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelButton)
	{
		LevelButton->OnClicked.AddDynamic(this, &ULevelItemWidget::OnPlayLevel);
	}
}

void ULevelItemWidget::SetLevelTextBlockName(const FName& LevelName)
{
	if (LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(LevelName));
	}
}

void ULevelItemWidget::SetLevelImage(UTexture2D* Image)
{
	if (LevelImage)
	{
		LevelImage->SetBrushFromTexture(Image, false);
	}
	ImageTexture = Image;
}

void ULevelItemWidget::OnPlayLevel()
{
	bIsClicked = true;
	OnAnimationStart.Broadcast(this);
}

void ULevelItemWidget::OnAnimationFinished(ULevelItemWidget* LevelWidget)
{
	if (!GetWorld() || !LevelWidget || !bIsClicked) return;

	const auto GameInstance = Cast<UATGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	GameInstance->SetCurrentLevelName(FName(LevelNameTextBlock->GetText().ToString()));
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelNameTextBlock->GetText().ToString()));
}
