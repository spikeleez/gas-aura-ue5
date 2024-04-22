// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttackAbility : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category="Core|Attack Ability")
	void ProcessAttackAbility();

	UFUNCTION(BlueprintPure, Category="Core|Attack Ability")
	float GetAttackSocketRadius() const;
	
	UPROPERTY(BlueprintReadOnly, Category="Attack Ability")
	FGameplayTag AttackMontageTag;

	UPROPERTY(BlueprintReadOnly, Category="Attack Ability")
	UAnimMontage* AttackMontage;

protected:
	UFUNCTION(BlueprintCallable, Category="Core|Attack Ability")
	void UpdateAvatarFacingTarget();

	UFUNCTION(BlueprintPure, Category="Core|Attack Ability")
	FVector GetCombatSocketLocation() const;

	UFUNCTION(BlueprintPure, Category="Core|Attack Ability")
	AActor* GetCombatTarget() const;

	UFUNCTION(BlueprintPure, Category="Core|Attack Ability")
	FVector GetCombatTargetLocation() const;

	UFUNCTION(BlueprintPure, Category="Core|Attack Ability")
	FTaggedMontage GetRandomAttackMontageInfos();
	
private:
	UPROPERTY(BlueprintReadOnly, Category="Attack Ability", meta=(AllowPrivateAccess="true"))
	FTaggedMontage AttackInfo;
};
