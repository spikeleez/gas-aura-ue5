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

	virtual void Die() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	virtual void BindCallbackHealthBarDelegates();

	UFUNCTION(BlueprintCallable, Category="Combat")
	virtual FVector GetCombatSocketLocation_Implementation() override;

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Data")
	TObjectPtr<UAuraCharacterData> CharacterData;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
