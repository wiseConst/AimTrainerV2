// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UTexture2D;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnimationStart, ULevelItemWidget*)

UCLASS()
class AIMTRAINER_API ULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetLevelTextBlockName(const FName& LevelName);
	void SetLevelImage(UTexture2D* Image);

	FOnAnimationStart OnAnimationStart;

	void OnAnimationFinished(ULevelItemWidget* LevelWidget);

	UPROPERTY()
	UTexture2D* ImageTexture;

	//CRUTCH 
	bool bIsClicked = false;

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* LevelButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* LevelImage;

	virtual void NativeOnInitialized() override;

private:

	UFUNCTION()
	void OnPlayLevel();
};
