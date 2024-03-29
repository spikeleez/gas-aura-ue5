// Copyright SpiKe Lee


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "Aura/Aura.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);

	/** Bind Native Actions - (Pressed) */
	AuraInputComponent->BindNativeAction(InputData, FAuraGameplayTags::Input_Native_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	AuraInputComponent->BindNativeAction(InputData, FAuraGameplayTags::Input_Native_Shift, ETriggerEvent::Triggered, this, &ThisClass::Input_ShiftPressed);
	
	/** Bind Native Actions - (Released) */
	AuraInputComponent->BindNativeAction(InputData, FAuraGameplayTags::Input_Native_Move, ETriggerEvent::Completed, this, &ThisClass::Input_Move);
	AuraInputComponent->BindNativeAction(InputData, FAuraGameplayTags::Input_Native_Shift, ETriggerEvent::Completed, this, &ThisClass::Input_ShiftReleased);
	
	/** Bind Ability Actions */
	AuraInputComponent->BindAbilityActions(InputData, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	if (GetASC() == nullptr) return;
	GetASC()->ProcessAbilityInput(DeltaTime, bGamePaused);
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_Ability_RMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	ClickToMove(InputTag, false);
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	ClickToMove(InputTag, true);
}

void AAuraPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, Value.Y);
		ControlledPawn->AddMovementInput(RightDirection, Value.X);
	}
}

void AAuraPlayerController::ClickToMove(const FGameplayTag& InputTag, const bool bInputPressed)
{
	// On Input Pressed / Held.
	if (bInputPressed)
	{
		if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_Ability_RMB))
		{
			if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
			return;
		}

		if (bTargeting || bShiftKeyDown)
		{
			if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		}
		else
		{
			FollowTime += GetWorld()->GetDeltaSeconds();
			if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;

			if (APawn* ControlledPawn = GetPawn())
			{
				const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
				ControlledPawn->AddMovementInput(WorldDirection);
			}
		}
	}
	// On Input Released
	else
	{
		if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_Ability_RMB))
		{
			if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
			return;
		}

		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		
		if (!bTargeting && !bShiftKeyDown)
		{
			const APawn* ControlledPawn = GetPawn();
			if (FollowTime <= ShortPressThreshold && ControlledPawn)
			{
				if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
					this, ControlledPawn->GetActorLocation(), CachedDestination))
				{
					Spline->ClearSplinePoints();
					for (const FVector& PointLocations : NavPath->PathPoints)
					{
						Spline->AddSplinePoint(PointLocations, ESplineCoordinateSpace::World);
					}
					if (NavPath->PathPoints.Num() > 0)
					{
						CachedDestination = NavPath->PathPoints.Last();
						bAutoRunning = true;
					}
				}
			}
			FollowTime = 0.f;
			bTargeting = false;
		}
	}
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Cursor, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent ==  nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}