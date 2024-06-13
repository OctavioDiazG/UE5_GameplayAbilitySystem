// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
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

void AAuraPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	/* this is for the enemies to glow when the cursor is on them
	Line trace from cursor. there are several scenarios:
	A. LastActor is null && ThisActor is null
		- do nothing
	B. LastActor is null && ThisActor is valid
		- call HighlightActor on ThisActor
	C. LastActor is valid && ThisActor is null
		- call UnhighlightActor on LastActor
	D. LastActor is valid && ThisActor is valid, but LastActor != ThisActor
		- call UnhighlightActor on LastActor
		- call HighlightActor on ThisActor
	E. LastActor is valid && ThisActor is valid, and LastActor == ThisActor
		- do nothing
	*/

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A - Both are null, do nothing
		}
	}
	else //LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			//Case C
			LastActor->UnhighlightActor();
		}
		else //Both Actors are valid
		{
			if (LastActor != ThisActor)
			{
				//Case D
				LastActor->UnhighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//Case E - Both are the same, do nothing
			}
		}
	}

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent-> BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

}
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();

	//depends on the type of movement you want to implement
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisValue.X);
	}

	
}

