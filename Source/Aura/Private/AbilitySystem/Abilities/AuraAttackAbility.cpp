// Copyright SpiKe Lee


#include "AbilitySystem/Abilities/AuraAttackAbility.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Interaction/EnemyInterface.h"

void UAuraAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	ProcessAttackAbility();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraAttackAbility::ProcessAttackAbility()
{
	AttackInfo = GetRandomAttackMontageInfos();
}

float UAuraAttackAbility::GetAttackSocketRadius() const
{
	return AttackInfo.AttackSocketRadius;
}

void UAuraAttackAbility::UpdateAvatarFacingTarget()
{
	ICombatInterface::Execute_UpdateFacingTargetLocation(GetAvatarActorFromActorInfo(), GetCombatTargetLocation());
}

FVector UAuraAttackAbility::GetCombatSocketLocation() const
{
	return ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), AttackMontageTag);
}

AActor* UAuraAttackAbility::GetCombatTarget() const
{
	if (GetAvatarActorFromActorInfo()) return IEnemyInterface::Execute_GetCombatTarget(GetAvatarActorFromActorInfo());
	return nullptr;
}

FVector UAuraAttackAbility::GetCombatTargetLocation() const
{
	if (GetCombatTarget()) return GetCombatTarget()->GetActorLocation();
	return FVector();
}

FTaggedMontage UAuraAttackAbility::GetRandomAttackMontageInfos()
{
	TArray<FTaggedMontage> TaggedMontages = ICombatInterface::Execute_GetAttackMontagesInfo(GetAvatarActorFromActorInfo());
	if (TaggedMontages.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, TaggedMontages.Num()-1);
	
		AttackMontage = TaggedMontages[RandomIndex].AttackMontage;
		AttackMontageTag = TaggedMontages[RandomIndex].AttackMontageTag;
	
		return TaggedMontages[RandomIndex];
	}
	return FTaggedMontage();
}
