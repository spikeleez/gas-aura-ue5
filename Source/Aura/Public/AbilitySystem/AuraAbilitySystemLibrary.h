// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Data/AuraCharacterData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Aura Ability System Library|Gameplay Effects")
	static void GiveGrantedAttributes(const UObject* WorldContext, const UAuraCharacterData* CharacterData, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="Aura Ability System Library|Gameplay Abilities")
	static void GiveGrantedAbilities(const UObject* WorldContext, UAuraCharacterData* CharacterData, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="Aura Ability System Library|Gameplay Abilities")
	static void GiveGrantedCommonAbilities(const UObject* WorldContext, const UAuraCharacterData* CharacterData, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Aura Ability System Library|Widget Controller")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContext = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Aura Ability System Library|Widget Controller")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContext = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Aura Ability System Library|Character Data")
	static UAuraCharacterData* GetCharacterData(const UObject* WorldContext, AActor* Actor);

	UFUNCTION(BlueprintPure, Category="Aura Ability System Library|Gameplay Effect")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="Aura Ability System Library|Gameplay Effect")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="Aura Ability System Library|Gameplay Effect")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bIsBlocked);

	UFUNCTION(BlueprintCallable, Category="Aura Ability System Library|Gameplay Effect")
	static void SetIsCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bIsCritical);
};
