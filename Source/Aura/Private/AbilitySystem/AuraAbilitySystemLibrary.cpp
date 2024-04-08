// Copyright SpiKe Lee


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AuraAbilityTypes.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Character/AuraCharacterBase.h"
#include "Data/AuraAbilitySetData.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

void UAuraAbilitySystemLibrary::GiveGrantedAttributes(const UObject* WorldContext, const UAuraCharacterData* CharacterData,
	UAbilitySystemComponent* ASC)
{
	const AActor* AvatarActor = ASC->GetAvatarActor();
	check(AvatarActor);
	check(ASC);
	check(CharacterData);

	if (const UAuraAbilitySetData* AbilitySet = Cast<UAuraAbilitySetData>(CharacterData->CharacterAbilitySet))
	{
		for (const FAuraAbilitySetData_GameplayEffect& GameplayEffects : AbilitySet->GrantedGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
			EffectContextHandle.AddSourceObject(AvatarActor);
			const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(
				GameplayEffects.GameplayEffect, GameplayEffects.EffectLevel, EffectContextHandle);

			ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}
}

void UAuraAbilitySystemLibrary::GiveGrantedAbilities(const UObject* WorldContext, UAuraCharacterData* CharacterData,
	UAbilitySystemComponent* ASC)
{
	check(ASC);
	check(CharacterData);

	if (const UAuraAbilitySetData* AbilitySet = Cast<UAuraAbilitySetData>(CharacterData->CharacterAbilitySet))
	{
		for (const FAuraAbilitySetData_GameplayAbility& GameplayAbilities : AbilitySet->GrantedGameplayAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbilities.GameplayAbility, GameplayAbilities.AbilityLevel);
			AbilitySpec.DynamicAbilityTags.AddTag(GameplayAbilities.AbilityTag);
			ASC->GiveAbility(AbilitySpec);
		}
		// TODO: Tag RelationShip Logic Here!
	}
}

void UAuraAbilitySystemLibrary::GiveGrantedCommonAbilities(const UObject* WorldContext,
	const UAuraCharacterData* CharacterData, UAbilitySystemComponent* ASC)
{
	check(ASC);
	check(CharacterData);

	if (const UAuraAbilitySetData* AbilitySet = Cast<UAuraAbilitySetData>(CharacterData->CharacterAbilitySet))
	{
		for (const FAuraCommonAbilitiesInfo AbilitiesInfo : AbilitySet->GrantedCommonAbilitiesData->CommonAbilitiesInfos)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilitiesInfo.Ability, AbilitiesInfo.AbilityLevel);
			AbilitySpec.DynamicAbilityTags.AddTag(AbilitiesInfo.AbilityTag);
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAuraCharacterData* UAuraAbilitySystemLibrary::GetCharacterData(const UObject* WorldContext, AActor* Actor)
{
	check(Actor);

	if (AAuraCharacterBase* CharacterBase = Cast<AAuraCharacterBase>(Actor))
	{
		if (UAuraCharacterData* CharacterData = Cast<UAuraCharacterData>(CharacterBase->GetCharacterData()))
		{
			return CharacterData;
		}
	}
	return nullptr;
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsCriticalHit();
	}
	return false;
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsBlocked)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsBlockedHit(bIsBlocked);
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bIsCritical)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsCriticalHit(bIsCritical);
	}
}
