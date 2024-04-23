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

UENUM(BlueprintType)
enum class EAuraEditCharDataMode: uint8
{
	Disabled,
	Minimal,
	Full,
};

USTRUCT(BlueprintType)
struct FAuraCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAuraEditCharDataMode CharacterEditMode = EAuraEditCharDataMode::Disabled;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="CharacterEditMode == EAuraEditCharDataMode::Minimal || CharacterEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	FName CharacterName = FName("Character Name");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="CharacterEditMode == EAuraEditCharDataMode::Minimal || CharacterEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	EAuraCharacterClass CharacterClass = EAuraCharacterClass::Warrior;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="CharacterEditMode == EAuraEditCharDataMode::Minimal || CharacterEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	USkeletalMesh* CharacterMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="CharacterEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	UTexture2D* CharacterIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="CharacterEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	UMaterialInstance* CharacterDissolveMaterial = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="CharacterEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	float CharacterLifeSpan = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="CharacterEditMode == EAuraEditCharDataMode::Minimal || CharacterEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	float CharacterBaseWalkSpeed = 250.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="CharacterEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	float CharacterRotationRate = 360.f;
};

USTRUCT(BlueprintType)
struct FAuraWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAuraEditCharDataMode WeaponEditMode = EAuraEditCharDataMode::Disabled;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="WeaponEditMode == EAuraEditCharDataMode::Minimal || WeaponEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	FName WeaponName = FName("Weapon Name");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="WeaponEditMode == EAuraEditCharDataMode::Minimal || WeaponEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	FName WeaponHandSocket = FName("WeaponHandSocket");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="WeaponEditMode == EAuraEditCharDataMode::Minimal || WeaponEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	EAuraWeaponClass WeaponClass = EAuraWeaponClass::Melee;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="WeaponEditMode == EAuraEditCharDataMode::Minimal || WeaponEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	USkeletalMesh* WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="WeaponEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	UTexture2D* WeaponIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="WeaponEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	UMaterialInstance* WeaponDissolveMaterial = nullptr;
};

USTRUCT(BlueprintType)
struct FAuraAnimationInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAuraEditCharDataMode AnimationEditMode = EAuraEditCharDataMode::Disabled;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="AnimationEditMode == EAuraEditCharDataMode::Minimal || AnimationEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	TSubclassOf<UAnimInstance> CharacterAnimClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="AnimationEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	TSubclassOf<UAnimInstance> WeaponAnimClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="AnimationEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	UAnimMontage* HitReactMontage = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="AnimationEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	TArray<FTaggedMontage> AttackMontages;
};

USTRUCT(BlueprintType)
struct FAuraAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAuraEditCharDataMode AbilityEditMode = EAuraEditCharDataMode::Disabled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="AbilityEditMode == EAuraEditCharDataMode::Minimal || AbilityEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	UAuraAbilitySetData* AbilitySetData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="AbilityEditMode == EAuraEditCharDataMode::Full", EditConditionHides))
	UCurveTable* DamageCalculationCoefficients = nullptr;
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
