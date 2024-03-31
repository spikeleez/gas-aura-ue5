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
	TSubclassOf<UGameplayAbility> Ability = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();
};

/**
 * 
 */
UCLASS(BlueprintType, Const)
class AURA_API UAuraCommonAbilitiesData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Common Abilities Info")
	TArray<FAuraCommonAbilitiesInfo> CommonAbilitiesInfos;
};
