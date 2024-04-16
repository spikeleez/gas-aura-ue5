// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraMeleeAttack : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category="Combat")
	void ProcessAttackAbility();
	
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	FGameplayTagContainer AttackTags = FGameplayTagContainer();

protected:
	UFUNCTION(BlueprintPure, Category="Combat")
	UAnimMontage* GetRandomAttackMontage();
};
