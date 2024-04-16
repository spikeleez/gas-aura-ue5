// Copyright SpiKe Lee


#include "Data/AuraCharacterData.h"

FAuraCharacterInfo UAuraCharacterData::GetCharacterInfoData() const
{
	return CharacterInfo;
}

FAuraAnimationInfo UAuraCharacterData::GetAnimationInfoData() const
{
	return AnimationInfo;
}

FAuraWeaponInfo UAuraCharacterData::GetWeaponInfoData() const
{
	return WeaponInfo;
}

FAuraAbilityInfo UAuraCharacterData::GetAbilityInfoData() const
{
	return AbilityInfo;
}
