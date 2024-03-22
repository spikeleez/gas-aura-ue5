// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Data/AuraCharacterData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

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

	UFUNCTION(BlueprintCallable, Category="Aura Ability System|Gameplay Abilities")
	static void GiveGrantedAbilities(const UObject* WorldContext, UAuraCharacterData* CharacterData, UAbilitySystemComponent* ASC);
};
