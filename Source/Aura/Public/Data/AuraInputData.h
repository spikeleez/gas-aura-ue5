// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputData.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FAuraInputData_NativeInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

USTRUCT(BlueprintType)
struct FAuraInputData_AbilityInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputData : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound = false) const;
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound = false) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAuraInputData_NativeInputActions> NativeInputActions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAuraInputData_AbilityInputActions> AbilityInputActions;
};
