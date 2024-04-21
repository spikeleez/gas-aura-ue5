// Copyright SpiKe Lee


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAuraDamageGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (AttackMontage && AttackMontageTag.IsValid()) AttackTaggedInfo = ProcessAttackMontageInfos();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	for (TTuple<FGameplayTag, FScalableFloat>& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);
	}
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

FTaggedMontage UAuraDamageGameplayAbility::ProcessAttackMontageInfos()
{
	TArray<FTaggedMontage> TaggedMontages = ICombatInterface::Execute_GetAttackMontagesInfo(GetAvatarActorFromActorInfo());
	int32 RandomIndex = FMath::RandRange(0, TaggedMontages.Num()-1);
	
	AttackMontage = TaggedMontages[RandomIndex].AttackMontage;
	AttackMontageTag = TaggedMontages[RandomIndex].AttackMontageTag;
	return TaggedMontages[RandomIndex];
}

float UAuraDamageGameplayAbility::GetAttackSocketRadius() const
{
	return AttackTaggedInfo.AttackSocketRadius;
}
