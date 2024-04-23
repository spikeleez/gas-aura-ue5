// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterData.generated.h"

class UAuraAbilitySetData;

UENUM(BlueprintType)
enum class EAuraCharacterClass : uint8
{
	Warrior,
	Wizard,
	Ranger,
};

UENUM(BlueprintType)
enum class EAuraWeaponClass : uint8
{
	Melee,
	Ranged,
	Special
};

USTRUCT(BlueprintType)
struct FAuraCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName CharacterName = "Character Name";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAuraCharacterClass CharacterClass = EAuraCharacterClass::Warrior;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* CharacterMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* CharacterIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* CharacterDissolveMaterial = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CharacterLifeSpan = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CharacterBaseWalkSpeed = 250.f;
};

USTRUCT(BlueprintType)
struct FAuraWeaponInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName WeaponName = "Weapon Name";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAuraWeaponClass WeaponClass = EAuraWeaponClass::Melee;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* WeaponIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* WeaponDissolveMaterial = nullptr;
};

USTRUCT(BlueprintType)
struct FAuraAnimationInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> CharacterAnimClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> WeaponAnimClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* HitReactMontage = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTaggedMontage> AttackMontages;
};

USTRUCT(BlueprintType)
struct FAuraAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAuraAbilitySetData* AbilitySetData;

	UPROPERTY(EditDefaultsOnly)
	UCurveTable* DamageCalculationCoefficients;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraCharacterData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="CharacterData")
	FAuraCharacterInfo GetCharacterInfoData() const;

	UFUNCTION(BlueprintPure, Category="CharacterData")
	FAuraAnimationInfo GetAnimationInfoData() const;

	UFUNCTION(BlueprintPure, Category="CharacterData")
	FAuraWeaponInfo GetWeaponInfoData() const;

	UFUNCTION(BlueprintPure, Category="CharacterData")
	FAuraAbilityInfo GetAbilityInfoData() const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterSettings")
	FAuraCharacterInfo CharacterInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimationSettings")
	FAuraAnimationInfo AnimationInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponSettings")
	FAuraWeaponInfo WeaponInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilitySettings")
	FAuraAbilityInfo AbilityInfo;
};
