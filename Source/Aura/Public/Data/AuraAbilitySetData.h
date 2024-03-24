// Copyright SpiKe Lee

#pragma once

#include "Engine/DataAsset.h"
#include "AuraAbilitySetData.generated.h"

class UAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FAuraAbilitySetData_GameplayEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.f;
};

USTRUCT(BlueprintType)
struct FAuraAbilitySetData_GameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> GameplayAbility = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// TODO: Add Input Tag Here!
};
/**
 * 
 */
UCLASS(BlueprintType, Const)
class UAuraAbilitySetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effects", meta=(TitleProperty=GameplayEffect))
	TArray<FAuraAbilitySetData_GameplayEffect> GrantedGameplayEffects;
	
	UPROPERTY(EditDefaultsOnly, Category="Gameplay Abilities", meta=(TitleProperty=GameplayAbility))
	TArray<FAuraAbilitySetData_GameplayAbility> GrantedGameplayAbilities;
};
