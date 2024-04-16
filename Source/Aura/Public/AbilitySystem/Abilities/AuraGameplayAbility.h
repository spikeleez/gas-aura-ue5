// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/AuraCharacterData.h"
#include "AuraGameplayAbility.generated.h"

class AAuraCharacterBase;
/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Aura|CharacterData")
	UAuraCharacterData* GetOwnerAbilityCharacterData();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Aura|CharacterData")
	AAuraCharacterBase* GetOwnerAbilityCharacterBase();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Aura|CharacterData|AnimMontage")
	UAnimMontage* GetOwnerAbilityCharacterDataHitReactAnimMontage();
};
