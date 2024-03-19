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
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Gameplay Effects|Effect")
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable, Category="Gameplay Effects|Overlap")
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category="Gameplay Effects|Overlap")
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay Effects")
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay Effects|Instant Gameplay Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay Effects|Instant Gameplay Effect")
	EAuraEffectApplicationPolicy InstantEffectApplicationPolicy = EAuraEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay Effects|Duration Gameplay Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay Effects|Duration Gameplay Effect")
	EAuraEffectApplicationPolicy DurationEffectApplicationPolicy = EAuraEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay Effects|Infinite Gameplay Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay Effects|Infinite Gameplay Effect")
	EAuraEffectApplicationPolicy InfiniteEffectApplicationPolicy = EAuraEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay Effects|Infinite Gameplay Effect")
	EAuraEffectRemovalPolicy InfiniteEffectRemovalPolicy = EAuraEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
};
