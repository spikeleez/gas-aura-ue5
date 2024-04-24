// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraMovementData.generated.h"

UENUM(BlueprintType)
enum class EAuraMovementGait : uint8
{
	Idle,
	Walking,
	Sprinting,
};

USTRUCT(BlueprintType)
struct FAuraMovementInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MovementTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAuraMovementGait MovementGait = EAuraMovementGait::Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeed = 0.f;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraMovementData : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Movement Data")
	float FindMovementSpeedByTag(FGameplayTag MovementTag);

	UFUNCTION(BlueprintPure, Category="Movement Data")
	float FindMovementSpeedByGait(EAuraMovementGait MovementGait);

	UFUNCTION(BlueprintPure, Category="Movement Data")
	TArray<FAuraMovementInfo> GetMovementInfo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defaults")
	float MovementRotationRate = 360.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	TArray<FAuraMovementInfo> MovementInfo;
};
