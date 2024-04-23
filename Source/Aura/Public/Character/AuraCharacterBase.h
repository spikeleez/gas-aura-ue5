// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Data/AuraCharacterData.h"
#include "Interaction/CombatInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraCharacterBase.generated.h"

class UWidgetComponent;
class UAuraCharacterData;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; };
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	UFUNCTION(BlueprintCallable, Category="AbilitySystem")
	void InitializeDefaultAttributes() const;
	
	UFUNCTION(BlueprintCallable, Category="AbilitySystem")
	void InitializeDefaultAbilities() const;

	UFUNCTION(BlueprintCallable, Category="Character Data|Character")
	void SetupCharacter(UAuraCharacterData* Data) const;

	UFUNCTION(BlueprintCallable, Category="Character Data|Weapon")
	void SetupWeapon(UAuraCharacterData* Data) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Character Data")
	UAuraCharacterData* GetCharacterData();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Character Data")
	EAuraCharacterClass GetCharacterClass();

	virtual void OnHitReactAbilityActivated(const FGameplayTag CallbackTag, int32 NewCount);

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();
	
	/* Combat Interface */
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual void Die() override;
	virtual TArray<FTaggedMontage> GetAttackMontagesInfo_Implementation() override;
	/* End Combat Interface */
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	virtual void BindCallbackHealthBarDelegates();

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Defaults")
	TObjectPtr<UAuraCharacterData> CharacterData;

	UPROPERTY(BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
