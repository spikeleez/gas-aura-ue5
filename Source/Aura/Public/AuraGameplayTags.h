// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

inline FName ConvertVariableNameToTagName(const FString& VariableName)
{
 const FString TagNameString = VariableName.Replace(TEXT("_"), TEXT("."));
 return FName(*TagNameString);
}

#define CREATE_NATIVE_TAG(VariableName, Description) \
static const FGameplayTag VariableName = UGameplayTagsManager::Get().AddNativeGameplayTag( \
ConvertVariableNameToTagName(TEXT(#VariableName)), \
FString(Description));

/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
 static const FAuraGameplayTags& Get() { return GameplayTags; }
 static void InitializeNativeGameplayTags();

 /* Primary Attribute Tags */
 inline CREATE_NATIVE_TAG(Attributes_Primary_Strength, "Increases Physical Damage.");
 inline CREATE_NATIVE_TAG(Attributes_Primary_Intelligence, "Increases Magical Damage.");
 inline CREATE_NATIVE_TAG(Attributes_Primary_Resilience, "Increases Armor and Armor Penetration.");
 inline CREATE_NATIVE_TAG(Attributes_Primary_Vigor, "Increases health.");

 /* Secondary Attribute Tags */
 inline CREATE_NATIVE_TAG(Attributes_Secondary_Armor, "Reduces Damage Taken, improves Block Chance.");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_ArmorPenetration, "Ignored Percentage of Enemy Armor, Increases Critical Hit Chance.");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_BlockChance, "Chance to cut incoming damage in half.");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_CriticalHitChance, "Chance to Double Damage Plus Critical Hit Bonus");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_CriticalHitDamage, "Bonus Damage added when a Critical Hit is Scored.");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_CriticalHitResistance, "Reduces Critical Hit Chance of Attacking Enemies.");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_HealthRegeneration, "Amount of Health Regenerated every time.");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_ManaRegeneration, "Amount of Mana Regenerated every time.");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_MaxHealth, "Maximum amount of Health Obtainable.");
 inline CREATE_NATIVE_TAG(Attributes_Secondary_MaxMana, "Maximum amount of Mana Obtainable.");

 /* Vital Attribute Tags */
 inline CREATE_NATIVE_TAG(Attributes_Vital_Health, "Amount of Health.");
 inline CREATE_NATIVE_TAG(Attributes_Vital_Mana, "Amount of Mana.");

 /* Input Tags */
 inline CREATE_NATIVE_TAG(InputTag_LMB, "Input Tag for Left Mouse Button");
 inline CREATE_NATIVE_TAG(InputTag_RMB, "Input Tag for Right Mouse Button");
 inline CREATE_NATIVE_TAG(InputTag_1, "Input Tag for 1 Key");
 inline CREATE_NATIVE_TAG(InputTag_2, "Input Tag for 2 Key");
 inline CREATE_NATIVE_TAG(InputTag_3, "Input Tag for 3 Key");
 inline CREATE_NATIVE_TAG(InputTag_4, "Input Tag for 4 Key");

private:
 static FAuraGameplayTags GameplayTags;
};
