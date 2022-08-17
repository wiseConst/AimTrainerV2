// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SettingOptionWidget.h"
#include "AimTrainer/Settings/ATGameSetting.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USettingOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(SettingDisplayName);
	check(SettingCurrentValueTextBlock);
	check(NextSettingButton);
	check(PrevSettingButton);

	NextSettingButton->OnClicked.AddDynamic(this, &USettingOptionWidget::OnNextSetting);
	PrevSettingButton->OnClicked.AddDynamic(this, &USettingOptionWidget::OnPrevSetting);
}

void USettingOptionWidget::Init(UATGameSetting* InSetting)
{
	Setting = MakeWeakObjectPtr(InSetting);
	check(Setting.IsValid());

	UpdateTexts();
}

void USettingOptionWidget::UpdateTexts()
{
	if (!Setting.IsValid()) return;

	SettingDisplayName->SetText(FText::FromString(Setting->GetName()));
	SettingCurrentValueTextBlock->SetText(FText::FromString(Setting->GetCurrentOption().Name));
}

void USettingOptionWidget::OnNextSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyNextOption();
		SettingCurrentValueTextBlock->SetText(FText::FromString(Setting->GetCurrentOption().Name));
	}
}

void USettingOptionWidget::OnPrevSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyPrevOption();
		SettingCurrentValueTextBlock->SetText(FText::FromString(Setting->GetCurrentOption().Name));	
	}
}