// Copyright SpiKe Lee


#include "AuraGameplayTags.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.DamageTypes.AddTag(GameplayTags.Damage_Fire);
}
