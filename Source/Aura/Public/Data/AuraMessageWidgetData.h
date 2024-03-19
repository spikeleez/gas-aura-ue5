// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraMessageWidgetData.generated.h"

class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FAuraMessageData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MessageText = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MessageIcon = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraMessageWidgetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Message Data")
	TArray<FAuraMessageData> MessageWidgetData;
};
