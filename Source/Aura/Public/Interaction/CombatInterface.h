// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* AttackMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttackMontageTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttackSocketLocation = FName("TipSocket");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSocketRadius = 45.f;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetCharacterLevel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="CombatInterface")
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="CombatInterface")
	void UpdateFacingTargetLocation(const FVector& Location);

	virtual void Die() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="CombatInterface")
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="CombatInterface")
	AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="CombatInterface")
	TArray<FTaggedMontage> GetAttackMontagesInfo();
};
