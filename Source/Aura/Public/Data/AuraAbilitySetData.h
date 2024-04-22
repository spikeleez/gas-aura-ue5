// Copyright SpiKe Lee

#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "AuraCommonAbilitiesData.h"
#include "AuraAbilitySetData.generated.h"

UENUM(BlueprintType)
enum class EAbilityActivationMethod : uint8
{
	BasedOnAbilityTags,
	BasedOnAbilityInputTag,
	Both
};

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
	EAbilityActivationMethod AbilityActivationMethod = EAbilityActivationMethod::BasedOnAbilityTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta=(ShortToolTip="Input Tag for Activation this Ability.",
		EditCondition="AbilityActivationMethod == EAbilityActivationMethod::BasedOnAbilityInputTag || AbilityActivationMethod == EAbilityActivationMethod::Both",
		EditConditionHides))
	FGameplayTag AbilityInputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta=(ShortToolTip="Ability Tags that will be added to the 'Ability Tags' container for that Ability.",
		EditCondition="AbilityActivationMethod == EAbilityActivationMethod::BasedOnAbilityTags || AbilityActivationMethod == EAbilityActivationMethod::Both",
		EditConditionHides))
	FGameplayTagContainer AbilityTags = FGameplayTagContainer();
};
/**
 * 
 */
UCLASS(BlueprintType, Const)
class UAuraAbilitySetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="GameplayEffects", meta=(TitleProperty=GameplayEffect))
	TArray<FAuraAbilitySetData_GameplayEffect> GrantedGameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category="GameplayAbilities", meta=(TitleProperty=GameplayAbility))
	TArray<FAuraAbilitySetData_GameplayAbility> GrantedGameplayAbilities;

	UPROPERTY(EditDefaultsOnly, Category="GameplayAbilities", meta=(TitleProperty=GameplayAbility))
	TObjectPtr<UAuraCommonAbilitiesData> GrantedCommonAbilities;
};
