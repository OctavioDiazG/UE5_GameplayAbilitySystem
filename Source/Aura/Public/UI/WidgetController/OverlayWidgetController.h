// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth); //the Delegate is used to broadcast the health value to the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BrodCastInitialValues() override;

	/*Because we made a DYNAMIC MULTICAST DELEGATE, and we made it BlueprintAssignable we can bind to this Delegate in Blueprints*/
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged; //FOnHealthChangedSignature is a delegate Type and OnHealthChanged is the delegate itself

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged; //FOnMaxHealthChangedSignature is a delegate Type and OnMaxHealthChanged is the delegate itself
};
