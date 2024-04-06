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
struct FAuraCharacterData_WeaponInfos
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName WeaponSocket = "TipSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* WeaponDissolveMaterialInstance = nullptr;
};

USTRUCT(BlueprintType)
struct FAuraCharacterData_CharacterAnimMontages
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* HitReactMontage = nullptr;
};

USTRUCT(BlueprintType)
struct FAuraCharacterData_CharacterInfos
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName CharacterName = "Character Name";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAuraCharacterClass CharacterClass = EAuraCharacterClass::Warrior;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> CharacterAnimClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* CharacterMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* CharacterIcon = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BodyLifeSpan = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* BodyDissolveMaterialInstance = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAuraCharacterData_WeaponInfos CharacterWeaponInfos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAuraCharacterData_CharacterAnimMontages CharacterAnimMontage;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraCharacterData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Defaults")
	FAuraCharacterData_CharacterInfos CharacterInfos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TObjectPtr<UAuraAbilitySetData> CharacterAbilitySet;

	UPROPERTY(EditDefaultsOnly, Category="Ability System")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;

	USkeletalMesh* GetCharacterMeshData() const;
	TSubclassOf<UAnimInstance> GetCharacterAnimClassData() const;
	FAuraCharacterData_CharacterInfos GetCharacterInfosData() const;
	FAuraCharacterData_CharacterAnimMontages GetCharacterAnimMontageData() const;
};
