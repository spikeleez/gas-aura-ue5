// Copyright SpiKe Lee


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	if (InWidgetController != nullptr)
	{
		WidgetController = InWidgetController;
		OnWidgetControllerSet(true);
	}
	else
	{
		OnWidgetControllerSet(false);
	}
}

FString UAuraUserWidget::GetAttributeNameByTag(const FGameplayTag& Tag)
{
	const FString TagString = Tag.GetTagName().ToString();

	int32 Index;
	if (TagString.FindLastChar('.', Index))
	{
		FString AttributeName = TagString.RightChop(Index + 1);
		return AttributeName;
	}
	return FString();
}
