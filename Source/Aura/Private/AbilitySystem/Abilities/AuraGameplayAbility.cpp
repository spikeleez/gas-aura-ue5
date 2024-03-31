// Copyright SpiKe Lee


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

#include "Character/AuraCharacterBase.h"

UAuraCharacterData* UAuraGameplayAbility::GetOwnerAbilityCharacterData()
{
	AAuraCharacterBase* AvatarCharacter = Cast<AAuraCharacterBase>(GetAvatarActorFromActorInfo());

	if (AvatarCharacter && AvatarCharacter->GetCharacterData())
	{
		return AvatarCharacter->GetCharacterData();
	}
	return nullptr;
}

UAnimMontage* UAuraGameplayAbility::GetOwnerAbilityCharacterDataHitReactAnimMontage()
{
	if (GetOwnerAbilityCharacterData())
	{
		if (UAnimMontage* HitReactMontage = GetOwnerAbilityCharacterData()->CharacterInfos.CharacterAnimMontage.HitReactMontage)
		{
			return HitReactMontage;
		}
	}
	return nullptr;
}
