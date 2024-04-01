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

TSubclassOf<UAnimInstance> UAuraCharacterData::GetCharacterAnimClassData() const
{
	if (CharacterInfos.CharacterAnimClass)
	{
		return CharacterInfos.CharacterAnimClass;
	}
	return nullptr;
}

FAuraCharacterData_CharacterInfos UAuraCharacterData::GetCharacterInfosData() const
{
	return CharacterInfos;
}

FAuraCharacterData_CharacterAnimMontages UAuraCharacterData::GetCharacterAnimMontageData() const
{
	return CharacterInfos.CharacterAnimMontage;
}
