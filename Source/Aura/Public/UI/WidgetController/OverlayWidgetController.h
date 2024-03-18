// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	void BindCallbacksToDependencies() const;

	UPROPERTY(BlueprintAssignable, Category="AbilitySystem|Attributes|Health")
	FOnAttributeChangedSignature OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category="AbilitySystem|Attributes|Health")
	FOnAttributeChangedSignature OnMaxHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category="AbilitySystem|Attributes|Mana")
	FOnAttributeChangedSignature OnManaChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category="AbilitySystem|Attributes|Mana")
	FOnAttributeChangedSignature OnMaxManaChangedDelegate;

private:
	void InitializeAttributeValues();
};
