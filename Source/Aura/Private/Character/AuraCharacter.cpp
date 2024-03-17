// Copyright SpiKe Lee


#include "Character/AuraCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAuraCharacter::AAuraCharacter()
{
	// Create the Spring Arm Component.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->ProbeSize = 16.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritRoll = false;
	SpringArm->TargetArmLength = 750.f;

	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->CameraRotationLagSpeed = 10.f;

	// Create the Camera Component.
	Camera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
	Camera->PostProcessSettings.MotionBlurAmount = 0.f;
	Camera->PostProcessSettings.MotionBlurMax = 0.f;
	Camera->PostProcessSettings.MotionBlurPerObjectSize = 0.f;
	Camera->PostProcessSettings.MotionBlurTargetFPS = 0;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, MovementRotationRate, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
