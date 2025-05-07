// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true; // Set this player controller to replicate in the network
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay(); // Call the parent class BeginPlay

	check(AuraContext); // Check if the AuraContext is valid
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); // Get the enhanced input subsystem from the local player
	if (Subsystem) //if the subsystem is valid
	{
		Subsystem->AddMappingContext(AuraContext, 0); // Add the mapping context to the subsystem
	}

	bShowMouseCursor = true; // Show the mouse cursor
	DefaultMouseCursor = EMouseCursor::Default; // Set the default mouse cursor to the default one

	FInputModeGameAndUI InputModeData; // Create a new input mode data object
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Set the mouse lock mode to not lock the mouse to the viewport
	InputModeData.SetHideCursorDuringCapture(false); // Set the cursor to be visible during capture
	SetInputMode(InputModeData); // Set the input mode to game and UI
	
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

void AAuraPlayerController::CursorTrace() //this function is used to trace the object under the cursor
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
	Super::SetupInputComponent(); // Call the parent class SetupInputComponent

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent); // Cast the input component to an enhanced input component

	EnhancedInputComponent-> BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move); // Bind the MoveAction to the Move function when the action is triggered

}
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>(); // Get the input axis value from the input action value

	//depends on the type of movement you want to implement
	const FRotator Rotation = GetControlRotation(); // Get the control rotation of the player controller
	const FRotator YawRotation(0, Rotation.Yaw, 0); // Create a new rotator with the yaw rotation of the control rotation

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Get the forward direction of the player controller
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Get the right direction of the player controller

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisValue.X);
	}

	
}

