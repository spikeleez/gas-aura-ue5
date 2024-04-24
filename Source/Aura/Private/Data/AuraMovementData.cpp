// Copyright SpiKe Lee


#include "Data/AuraMovementData.h"


float UAuraMovementData::FindMovementSpeedByTag(FGameplayTag MovementTag)
{
	for (const FAuraMovementInfo Info : MovementInfo)
	{
		if (Info.MovementTag.MatchesTagExact(MovementTag))
		{
			return Info.MovementSpeed;
		}
	}
	return 0.f;
}

float UAuraMovementData::FindMovementSpeedByGait(EAuraMovementGait MovementGait)
{
	for (const FAuraMovementInfo Info : MovementInfo)
	{
		if (Info.MovementGait == MovementGait)
		{
			return Info.MovementSpeed;
		}
	}
	return 0.f;
}

TArray<FAuraMovementInfo> UAuraMovementData::GetMovementInfo()
{
	return MovementInfo;
}
