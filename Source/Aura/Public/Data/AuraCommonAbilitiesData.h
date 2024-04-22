// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraCommonAbilitiesData.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FAuraCommonAbilitiesInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> GameplayAbility = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ShortTooltip="Ability Tags that will be added to the 'Ability Tags' container for that Ability."))
	FGameplayTagContainer AbilityTags = FGameplayTagContainer();
};

/**
 * 
 */
UCLASS(BlueprintType, Const)
class AURA_API UAuraCommonAbilitiesData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilitySettings")
	TArray<FAuraCommonAbilitiesInfo> CommonAbilitiesInfo;
};
