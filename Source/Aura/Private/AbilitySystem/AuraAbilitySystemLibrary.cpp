// Copyright SpiKe Lee


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Data/AuraAbilitySetData.h"

void UAuraAbilitySystemLibrary::GiveGrantedAttributes(const UObject* WorldContext, const UAuraCharacterData* CharacterData,
	UAbilitySystemComponent* ASC)
{
	const AActor* AvatarActor = ASC->GetAvatarActor();
	check(AvatarActor);
	check(ASC);

	for (const FAuraAbilitySetData_GameplayEffect& GameplayEffects : CharacterData->CharacterAbilitySet->GrantedGameplayEffects)
	{
		FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(
			GameplayEffects.GameplayEffect, GameplayEffects.EffectLevel, EffectContextHandle);
		
		ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UAuraAbilitySystemLibrary::GiveGrantedAbilities(const UObject* WorldContext, UAuraCharacterData* CharacterData,
	UAbilitySystemComponent* ASC)
{
	check(ASC);
	for (const FAuraAbilitySetData_GameplayAbility& GameplayAbilities : CharacterData->CharacterAbilitySet->GrantedGameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(
			GameplayAbilities.GameplayAbility, GameplayAbilities.AbilityLevel);
		
		// TODO: Add Gameplay Input tag to Ability System
		//AbilitySpec.DynamicAbilityTags.AddTag(GameplayAbilities.InputTag);
		ASC->GiveAbility(AbilitySpec);
	}

	// TODO: Tag RelationShip Logic Here!
}