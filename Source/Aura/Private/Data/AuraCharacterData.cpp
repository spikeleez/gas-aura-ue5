// Copyright SpiKe Lee


#include "Data/AuraCharacterData.h"


USkeletalMesh* UAuraCharacterData::GetCharacterMeshData() const
{
	if (CharacterInfos.CharacterMesh)
	{
		return CharacterInfos.CharacterMesh;
	}
	return nullptr;
}

EAuraCharacterClass UAuraCharacterData::GetCharacterClassData() const
{
	return CharacterInfos.CharacterClass;
}

TSubclassOf<UAnimInstance> UAuraCharacterData::GetCharacterAnimClassData() const
{
	if (CharacterInfos.CharacterAnimClass)
	{
		return CharacterInfos.CharacterAnimClass;
	}
	return nullptr;
}

USkeletalMesh* UAuraCharacterData::GetWeaponMeshData() const
{
	if (CharacterInfos.WeaponInfos.WeaponMesh)
	{
		return CharacterInfos.WeaponInfos.WeaponMesh;
	}
	return nullptr;
}

UTexture2D* UAuraCharacterData::GetCharacterIconData() const
{
	if (CharacterInfos.CharacterIcon)
	{
		return CharacterInfos.CharacterIcon;
	}
	return nullptr;
}

FName UAuraCharacterData::GetCharacterNameData() const
{
	if (CharacterInfos.CharacterName != "")
	{
		return CharacterInfos.CharacterName;
	}
	return "";
}

FAuraCharacterData_WeaponInfos UAuraCharacterData::GetCharacterWeaponInfos() const
{
	if (CharacterInfos.WeaponInfos.WeaponMesh == nullptr) return FAuraCharacterData_WeaponInfos();
	return CharacterInfos.WeaponInfos;
}
