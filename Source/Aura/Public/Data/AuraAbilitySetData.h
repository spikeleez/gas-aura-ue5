// Copyright SpiKe Lee

#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "AuraCommonAbilitiesData.h"
#include "AuraAbilitySetData.generated.h"

class UAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FAuraAbilitySetData_GameplayEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EffectLevel = 1.f;
};

USTRUCT(BlueprintType)
struct FAuraAbilitySetData_GameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> GameplayAbility = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();
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

	UPROPERTY(EditDefaultsOnly, Category="Common Abilities", meta=(TitleProperty=GameplayAbility))
	TObjectPtr<UAuraCommonAbilitiesData> GrantedCommonAbilitiesData;
};
