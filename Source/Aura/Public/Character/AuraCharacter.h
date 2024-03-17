// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	
	UPROPERTY(EditAnywhere, Category="Player|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, Category="Player|Camera")
	TObjectPtr<UCameraComponent> Camera;

private:
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float MovementRotationRate = 400.f;
};
