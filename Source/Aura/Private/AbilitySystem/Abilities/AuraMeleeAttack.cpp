// Copyright SpiKe Lee


#include "AbilitySystem/Abilities/AuraMeleeAttack.h"

#include "AuraGameplayTags.h"

void UAuraMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	ProcessAttackAbility();
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraMeleeAttack::ProcessAttackAbility()
{
	const TMap<FGameplayTag, UAnimMontage*> AttackMontages = GetOwnerAbilityCharacterData()->AnimationInfo.AttackMontages;

	for (const TTuple<FGameplayTag, UAnimMontage*>& Pair : AttackMontages)
	{
		const FGameplayTag Tag = Pair.Key;
		if (Tag.MatchesTag(FAuraGameplayTags::Get().Montage_Attack_Melee))
		{
			AttackTags.AddTag(Tag);
		}
	}
}

UAnimMontage* UAuraMeleeAttack::GetRandomAttackMontage()
{
	TMap<FGameplayTag, UAnimMontage*> AttackMontages = GetOwnerAbilityCharacterData()->AnimationInfo.AttackMontages;

	if (!AttackTags.IsEmpty())
	{
		TArray<FGameplayTag> TagsArray;
		AttackTags.GetGameplayTagArray(TagsArray);

		const int32 RandomIndex = FMath::RandRange(0, TagsArray.Num() - 1);
		const FGameplayTag RandomTag = TagsArray[RandomIndex];

		if (UAnimMontage** MontageToPlay = AttackMontages.Find(RandomTag))
		{
			return *MontageToPlay;
		}
	}
	return nullptr;
}
