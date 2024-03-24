// Copyright SpiKe Lee


#include "Data/AuraAttributeData.h"

FAuraAttributeInfo UAuraAttributeData::FindAttributeInfoByTag(const FGameplayTag& AttributeTag, const bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInfo)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
