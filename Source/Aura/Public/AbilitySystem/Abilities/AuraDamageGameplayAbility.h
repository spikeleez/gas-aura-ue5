// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
