// Copyright SpiKe Lee


#include "Data/AuraInputData.h"

const UInputAction* UAuraInputData::FindNativeInputActionForTag(const FGameplayTag& InputTag,
	const bool bLogNotFound) const
{
	for (const FAuraInputData_NativeInputActions& Action : NativeInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find NativeInputAction for InputTag [%s], on InputData [%s]"),
			*InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* UAuraInputData::FindAbilityInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound) const
{
	for (const FAuraInputData_AbilityInputActions& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputData [%s]"),
			*InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
