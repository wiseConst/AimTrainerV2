// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChoseLevelWidget.generated.h"

class UHorizontalBox;
class UImage;
class UWidgetAnimation;
class ULevelItemWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnimationFinished, ULevelItemWidget*)

UCLASS()
class AIMTRAINER_API UChoseLevelWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	FOnAnimationFinished OnAnimationFinished;

	UPROPERTY()
	ULevelItemWidget* ChosenLevelWidget = nullptr;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelHorizontalBox;

	UPROPERTY(meta = (BindWidget))
	UImage* LoadImage;

	UPROPERTY(meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* LoadingAnimation;

	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation);

private:
	void InitLevels();

	void PlayLoadAnimation(ULevelItemWidget* UserWidget);
};
