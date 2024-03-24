// Copyright SpiKe Lee


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Data/AuraAttributeData.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeData);

	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& Pair : AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeData->FindAttributeInfoByTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}
