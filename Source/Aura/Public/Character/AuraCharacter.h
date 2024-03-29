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

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(EditAnywhere, Category="Player|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, Category="Player|Camera")
	TObjectPtr<UCameraComponent> Camera;
	
	/* Combat Interface */
	virtual int32 GetCharacterLevel() override;
	/* End Combat Interface */

protected:
	virtual void InitAbilityActorInfo() override;
	virtual void BindCallbackHealthBarDelegates() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float MovementRotationRate = 400.f;
};
