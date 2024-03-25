// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTags.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Widget Controller")
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<UObject> WidgetController;

	// Debug Only
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AbilitySystem|Attributes")
	FString GetAttributeNameByTag(const FGameplayTag& Tag);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet(bool bWasSuccessful = false);
};
