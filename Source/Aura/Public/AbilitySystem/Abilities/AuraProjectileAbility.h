// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "AuraAttackAbility.h"
#include "AuraProjectileAbility.generated.h"

class AAuraProjectile;

/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileAbility : public UAuraAttackAbility
{
	GENERATED_BODY()

public:
	UAuraProjectileAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectileSpell(const FVector& ProjectileTargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	TSubclassOf<AAuraProjectile> ProjectileClass;

private:
	UPROPERTY()
	FVector SpawnSocketLocation;
};
