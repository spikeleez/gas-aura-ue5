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
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category="Damage")
	void CauseDamage(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category="Core|Attack")
	FTaggedMontage ProcessAttackMontageInfos();

	UFUNCTION(BlueprintPure, Category="Core|Attack")
	float GetAttackSocketRadius() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack")
	float AttackRadius = 45.f;
	
	UPROPERTY(BlueprintReadOnly, Category="Attack")
	FGameplayTag AttackMontageTag;

	UPROPERTY(BlueprintReadOnly, Category="Attack")
	UAnimMontage* AttackMontage;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UPROPERTY(BlueprintReadOnly, Category="Attack")
	FTaggedMontage AttackTaggedInfo;
};
