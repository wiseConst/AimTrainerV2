// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGameSetting.h"

void UATGameSetting::SetName(const FString& InName)
{
	Name = InName;
}
void UATGameSetting::SetOptions(const TArray<FSettingOption>& InOptions)
{
	Options = InOptions;
}

FSettingOption UATGameSetting::GetCurrentOption() const
{
	const int32 CurrentValue = GetCurrentValue();
	const auto Option = Options.FindByPredicate(
		[&](const auto& Opt)
		{
			return Opt.Value == CurrentValue;
		});
	if (!Option) return FSettingOption{};

	return *Option;
}

const FString& UATGameSetting::GetName() const
{
	return Name;
}

void UATGameSetting::SetCurrentValue(int32 Value)
{
	if (!Setter) return;
	Setter(Value);
}

void UATGameSetting::ApplyNextOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;

	const int32 NextIndex = (CurrentIndex + 1) % Options.Num();
	SetCurrentValue(Options[NextIndex].Value);
}

void UATGameSetting::ApplyPrevOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE) return;

	const int32 PrevIndex = CurrentIndex == 0 ? Options.Num() - 1 : CurrentIndex - 1;
	SetCurrentValue(Options[PrevIndex].Value);
}

void UATGameSetting::AddGetter(TFunction<int32()> Func)
{
	Getter = Func;
}

void UATGameSetting::AddSetter(TFunction<void(int32)> Func)
{
	Setter = Func;
}

int32 UATGameSetting::GetCurrentValue() const
{
	if (!Getter) return INDEX_NONE;
	return Getter();
}

int32 UATGameSetting::GetCurrentIndex() const
{
	const int32 CurrentValue = GetCurrentValue();
	return Options.IndexOfByPredicate(
		[&](const auto& Opt)
		{
			return CurrentValue == Opt.Value;
		});
}