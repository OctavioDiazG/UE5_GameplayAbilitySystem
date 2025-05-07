// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController(); // Generate the Definition for the constructor

	virtual void Tick(float DeltaTime) override;
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override; // Set up the input component for the player controller

private:
	UPROPERTY(EditAnywhere, Category = "Input") // UPROPERTY is a macro that allows the variable to be edited in the editor in the specified category
	TObjectPtr<UInputMappingContext> AuraContext; // Input mapping context for the player controller

	UPROPERTY(EditAnywhere, Category = "Input") 
	TObjectPtr<UInputAction> MoveAction;

	void CursorTrace(); //initialize the function to trace the object under the cursor
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	
	void Move(const FInputActionValue& InputActionValue); //initialize the function to move the player controller
};
