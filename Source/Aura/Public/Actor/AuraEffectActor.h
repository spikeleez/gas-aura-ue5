// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM()
enum class EAuraEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM()
enum class EAuraEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	UFUNCTION(BlueprintCallable, Category="GameplayEffects|Effect")
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable, Category="GameplayEffects|Overlap")
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category="GameplayEffects|Overlap")
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects")
	bool bDestroyOnEffectApplication = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects")
	bool bApplyEffectsToEnemies = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects")
	float ActorLevel = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects|InstantGameplayEffect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects|InstantGameplayEffect")
	EAuraEffectApplicationPolicy InstantEffectApplicationPolicy = EAuraEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects|DurationGameplayEffect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects|DurationGameplayEffect")
	EAuraEffectApplicationPolicy DurationEffectApplicationPolicy = EAuraEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects|InfiniteGameplayEffect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects|InfiniteGameplayEffect")
	EAuraEffectApplicationPolicy InfiniteEffectApplicationPolicy = EAuraEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffects|InfiniteGameplayEffect")
	EAuraEffectRemovalPolicy InfiniteEffectRemovalPolicy = EAuraEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
};
