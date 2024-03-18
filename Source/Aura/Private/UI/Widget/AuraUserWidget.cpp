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
