// Copyright SpiKe Lee


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
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

	if (const UAuraAbilitySetData* AbilitySet = Cast<UAuraAbilitySetData>(CharacterData->AbilityInfo.AbilitySetData))
	{
		for (const FAuraAbilitySetData_GameplayEffect& GameplayEffects : AbilitySet->GrantedGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
			EffectContextHandle.AddSourceObject(AvatarActor);
			const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffects.GameplayEffect, GameplayEffects.EffectLevel, EffectContextHandle);
			ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}
}

void UAuraAbilitySystemLibrary::GiveGrantedAbilities(const UObject* WorldContext, UAuraCharacterData* CharacterData,
	UAbilitySystemComponent* ASC)
{
	check(ASC);
	check(CharacterData);

	if (const UAuraAbilitySetData* AbilitySet = Cast<UAuraAbilitySetData>(CharacterData->AbilityInfo.AbilitySetData))
	{
		for (const FAuraAbilitySetData_GameplayAbility& GameplayAbilities : AbilitySet->GrantedGameplayAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbilities.GameplayAbility, GameplayAbilities.AbilityLevel);
			if (GameplayAbilities.AbilityActivationMethod == EAbilityActivationMethod::Both)
			{
				AbilitySpec.DynamicAbilityTags.AddTag(GameplayAbilities.AbilityInputTag);
				for (const FGameplayTag& Tags : GameplayAbilities.AbilityTags)
				{
					if (!Tags.MatchesTag(FAuraGameplayTags::Get().Input)) AbilitySpec.Ability->AbilityTags.AddTag(Tags);
				}
			}
			if (GameplayAbilities.AbilityActivationMethod == EAbilityActivationMethod::BasedOnAbilityTags)
			{
				for (const FGameplayTag& Tags : GameplayAbilities.AbilityTags)
				{
					if (!Tags.MatchesTag(FAuraGameplayTags::Get().Input)) AbilitySpec.Ability->AbilityTags.AddTag(Tags);
				}
			}
			if (GameplayAbilities.AbilityActivationMethod == EAbilityActivationMethod::BasedOnAbilityInputTag)
			{
				AbilitySpec.DynamicAbilityTags.AddTag(GameplayAbilities.AbilityInputTag);
			}
			ASC->GiveAbility(AbilitySpec);
		}
		//TODO: Tag RelationShip Logic Here!
	}
}

void UAuraAbilitySystemLibrary::GiveGrantedCommonAbilities(const UObject* WorldContext, const UAuraCharacterData* CharacterData,
	UAbilitySystemComponent* ASC)
{
	check(ASC);
	check(CharacterData);

	if (const UAuraAbilitySetData* AbilitySet = Cast<UAuraAbilitySetData>(CharacterData->AbilityInfo.AbilitySetData))
	{
		for (const FAuraCommonAbilitiesInfo Ability : AbilitySet->GrantedCommonAbilities->CommonAbilitiesInfo)
		{
			// TODO: Change Ability Spec Level Based (Level of Character has this ability).
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability.GameplayAbility, Ability.AbilityLevel);
			for (const FGameplayTag& Tags : Ability.AbilityTags)
			{
				if (!Tags.MatchesTag(FAuraGameplayTags::Get().Input)) AbilitySpec.Ability->AbilityTags.AddTag(Tags);
			}
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

UAuraCharacterData* UAuraAbilitySystemLibrary::AuraGetCharacterData(const UObject* WorldContext, AActor* Actor)
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

EAuraCharacterClass UAuraAbilitySystemLibrary::AuraGetCharacterClass(const UObject* WorldContext, UAuraCharacterData* CharacterData)
{
	check(CharacterData);
	return CharacterData->CharacterInfo.CharacterClass;
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
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.
		Get()))
	{
		AuraEffectContext->SetIsCriticalHit(bIsCritical);
	}
}

void UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContext, TArray<AActor*>& OutOverlappingActors,
		const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(
			Overlaps,
			SphereOrigin,
			FQuat::Identity,
			FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
			FCollisionShape::MakeSphere(Radius),
			SphereParams
		);
		for (FOverlapResult& OverlapResult : Overlaps)
		{
			if (OverlapResult.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(OverlapResult.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(OverlapResult.GetActor()));
			}
		}
	}
}

bool UAuraAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriends = bBothArePlayers || bBothAreEnemies;
	return !bFriends;
}
