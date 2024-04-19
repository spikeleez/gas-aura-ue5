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
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffects")
	static void GiveGrantedAttributes(const UObject* WorldContext, const UAuraCharacterData* CharacterData,
		UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayAbilities")
	static void GiveGrantedAbilities(const UObject* WorldContext, UAuraCharacterData* CharacterData,
		UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayAbilities")
	static void GiveGrantedCommonAbilities(const UObject* WorldContext, const UAuraCharacterData* CharacterData,
		UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContext = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContext = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AuraAbilitySystemLibrary|CharacterData")
	static UAuraCharacterData* AuraGetCharacterData(const UObject* WorldContext, AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AuraAbilitySystemLibrary|CharacterData")
	static EAuraCharacterClass AuraGetCharacterClass(const UObject* WorldContext, UAuraCharacterData* CharacterData);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bIsBlocked);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bIsCritical);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* WorldContext, TArray<AActor*>& OutOverlappingActors,
		const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);
};
