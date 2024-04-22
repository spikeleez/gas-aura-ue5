// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "AuraAttackAbility.h"
#include "AuraMeleeAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraMeleeAbility : public UAuraAttackAbility
{
	GENERATED_BODY()

public:
	UAuraMeleeAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
