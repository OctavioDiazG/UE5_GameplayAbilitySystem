// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)

struct FWidgetControllerParams // this is a struct that will hold all the data that we need to pass to the widget controller
{
	GENERATED_BODY()

	FWidgetControllerParams() {} // default constructor
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {} // constructor that takes in all the data that we need to pass to the widget controller

	UPROPERTY(EditAnywhere, BlueprintReadWrite) // this will allow us to edit this data in the editor
	TObjectPtr<APlayerController> PlayerController = nullptr; // this is the player controller that we are going to pass to the widget controller
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) // this will allow us to edit this data in the editor
	TObjectPtr<APlayerState> PlayerState = nullptr;	// this is the player state that we are going to pass to the widget controller
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) // this will allow us to edit this data in the editor 
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr; // this is the ability system component that we are going to pass to the widget controller
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) // this will allow us to edit this data in the editor 
	TObjectPtr<UAttributeSet> AttributeSet = nullptr; // this is the attribute set that we are going to pass to the widget controller
}; 

/**
* widget controller is going to be responsible for getting any data from the system, from the model in this architecture.
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams); // this function will be called by the game mode to set the widget controller params

	virtual void BrodCastInitialValues(); // this function will be called by the game mode to broadcast the initial values to the widget
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	
};
