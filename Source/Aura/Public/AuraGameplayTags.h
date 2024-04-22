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

 /* Resistances Attributes */
 inline CREATE_NATIVE_TAG(Attributes_Resistance_Fire, "A Fire Resistance Tag.");
 inline CREATE_NATIVE_TAG(Attributes_Resistance_Lightning, "A Lightning Resistance Tag.");
 inline CREATE_NATIVE_TAG(Attributes_Resistance_Arcane, "A Arcane Resistance Tag.");
 inline CREATE_NATIVE_TAG(Attributes_Resistance_Physical, "A Physical Resistance Tag.");

 /* Input Tags */
 inline CREATE_NATIVE_TAG(Input, "Simple Input Tag.");
 inline CREATE_NATIVE_TAG(Input_Native_Move, "Native Input Tag for Move Action");
 inline CREATE_NATIVE_TAG(Input_Native_Shift, "Native Input Tag for Shift Key");
 inline CREATE_NATIVE_TAG(Input_Ability_LMB, "Ability Input Tag for Left Mouse Button");
 inline CREATE_NATIVE_TAG(Input_Ability_RMB, "Ability Input Tag for Right Mouse Button");
 inline CREATE_NATIVE_TAG(Input_Ability_1, "Ability Input Tag for 1 Key");
 inline CREATE_NATIVE_TAG(Input_Ability_2, "Ablity Input Tag for 2 Key");
 inline CREATE_NATIVE_TAG(Input_Ability_3, "Ability Input Tag for 3 Key");
 inline CREATE_NATIVE_TAG(Input_Ability_4, "Ability Input Tag for 4 Key");

 /* Damages Tags */
 TMap<FGameplayTag, FGameplayTag> DamageTypesToResistance;
 
 inline CREATE_NATIVE_TAG(Damage, "A Damage Tag.");
 inline CREATE_NATIVE_TAG(Damage_Fire, "A Fire Damage Type Tag.");
 inline CREATE_NATIVE_TAG(Damage_Lightning, "A Lightning Damage Type Tag.");
 inline CREATE_NATIVE_TAG(Damage_Arcane, "A Arcane Damage Type Tag.");
 inline CREATE_NATIVE_TAG(Damage_Physical, "A Physical Damage Type Tag.");

 /* Abilities Tag */
 inline CREATE_NATIVE_TAG(Abilities_Action_HitReact, "A Ability Hit React Tag.");
 inline CREATE_NATIVE_TAG(Abilities_Action_Attack, "A Simple tag for Attack Abilities.");

 /* Status Tag */
 inline CREATE_NATIVE_TAG(Status_Effect_HitReact, "A Hit React Status Tag.");

 /* Montage Tags */
 inline CREATE_NATIVE_TAG(Montage, "A Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack, "A Montage Attack Tag");
 
 inline CREATE_NATIVE_TAG(Montage_Attack_Melee, "For Melee Montage Attacks Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Melee_Weapon, "A Melee Weapon Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Melee_Weapon_A, "A Melee Weapon A Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Melee_Weapon_B, "A Melee Weapon B Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Melee_Weapon_C, "A Melee Weapon C Attack Montage Tag");

 inline CREATE_NATIVE_TAG(Montage_Attack_Melee_Unarmed, "A Melee Unarmed Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Melee_Unarmed_A, "A Melee Unarmed A Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Melee_Unarmed_B, "A Melee Unarmed B Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Melee_Unarmed_C, "A Melee Unarmed C Attack Montage Tag");

 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged, "For Ranged Montage Attacks Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged_Weapon, "A Ranged Weapon Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged_Weapon_A, "A Ranged A Weapon Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged_Weapon_B, "A Ranged B Weapon Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged_Weapon_C, "A Ranged C Weapon Attack Montage Tag");

 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged_Unarmed, "A Ranged Unarmed Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged_Unarmed_A, "A Ranged A Unarmed Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged_Unarmed_B, "A Ranged B Unarmed Attack Montage Tag");
 inline CREATE_NATIVE_TAG(Montage_Attack_Ranged_Unarmed_C, "A Ranged C Unarmed Attack Montage Tag");

private:
 static FAuraGameplayTags GameplayTags;
};
