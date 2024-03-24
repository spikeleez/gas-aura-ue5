// Copyright SpiKe Lee


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	InitializeAttributeValues();
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	/* Bind Health Attributes */
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnHealthChangedDelegate.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
	});
	/* End Bind of Health Attributes */

	/* Bind Mana Attributes */
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnManaChangedDelegate.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChangedDelegate.Broadcast(Data.NewValue);
	});
	
	/* End Bind of Mana Attributes */

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag Tag : AssetTags)
		{
			if (Tag.MatchesTag(FindMessageDataIndexByTag(Tag).MessageTag))
			{
				OnReceiveMessageDataDelegate.Broadcast(FindMessageDataIndexByTag(Tag));
			}
			else
			{
				const FString Msg = FString::Printf(TEXT("Not found Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, Msg);
			}
		}
	});
}

FAuraMessageData UOverlayWidgetController::FindMessageDataIndexByTag(const FGameplayTag Tag)
{
	for (const FAuraMessageData MessageData : MessageWidgetData->MessageData)
	{
		if (MessageData.MessageTag.MatchesTag(Tag))
		{
			return MessageData;
		}
	}
	return FAuraMessageData();
}

void UOverlayWidgetController::InitializeAttributeValues() const
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChangedDelegate.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChangedDelegate.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChangedDelegate.Broadcast(AuraAttributeSet->GetMaxMana());
}
