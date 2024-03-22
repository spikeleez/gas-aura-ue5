// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AuraCharacterData.generated.h"

class UAuraAbilitySetData;

UENUM()
enum class EAuraCharacterClass : uint8
{
	Warrior,
	Wizard,
	Ranger,
	MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FAuraCharacterData_CharacterInfos
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Infos")
	FName CharacterName = "Character Name";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Infos")
	EAuraCharacterClass CharacterClass = EAuraCharacterClass::Warrior;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Infos")
	TSubclassOf<UAnimInstance> CharacterAnimClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Infos")
	USkeletalMesh* CharacterMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Infos")
	USkeletalMesh* WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Infos")
	UTexture2D* CharacterIcon = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraCharacterData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Default Infos")
	FAuraCharacterData_CharacterInfos CharacterInfos;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Ability Infos")
	UAuraAbilitySetData* CharacterAbilitySet;

	USkeletalMesh* GetCharacterMeshData() const;
	EAuraCharacterClass GetCharacterClassData() const;
	TSubclassOf<UAnimInstance> GetCharacterAnimClassData() const;
	USkeletalMesh* GetWeaponMeshData() const;
	UTexture2D* GetCharacterIconData() const;
	FName GetCharacterNameData() const;
};
