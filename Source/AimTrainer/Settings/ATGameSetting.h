// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATGameSetting.generated.h"

USTRUCT()
struct FSettingOption
{
	GENERATED_USTRUCT_BODY()

	FSettingOption()
	{
		Name = FString("");
		Value = 0;
	}

	FSettingOption(const FString& InName, int32 InValue)
		: Name(InName)
		, Value(InValue)
	{
	}

	FString Name;

	int32 Value;
};

UCLASS()
class UATGameSetting : public UObject
{
	GENERATED_BODY()

public:

	void SetName(const FString& InName);
	void SetOptions(const TArray<FSettingOption>& InOptions);

	FSettingOption GetCurrentOption() const;
	const FString& GetName() const;

	void AddGetter(TFunction<int32()> Func);
	void AddSetter(TFunction<void(int32)> Func);

	void ApplyNextOption();
	void ApplyPrevOption();

private:

	FString Name;
	TArray<FSettingOption> Options;
	TFunction<int32()> Getter;
	TFunction<void(int32)> Setter;

	int32 GetCurrentValue() const;
	void SetCurrentValue(int32 Value);
	int32 GetCurrentIndex() const;
};
