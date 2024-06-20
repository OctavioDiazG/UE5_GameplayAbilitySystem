// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

//NOTE: Here we are declaring the Delegates that we are going to use to broadcast the changes to the UI 
//we create this delegates to broadcast the changes to the UI (OverlayWidget)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth); //the Delegate is used to broadcast the health value to the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth); //the Delegate is used to broadcast the MaxHealth value to the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana); //the Delegate is used to broadcast the Mana value to the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana); //the Delegate is used to broadcast the MaxMana value to the UI

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BrodCastInitialValues() override; //this function will broadcast the initial values to the UI
	virtual void BindCallBacksToDependencies() override; //this function will bind the callbacks to the dependencies

	/*Because we made a DYNAMIC MULTICAST DELEGATE, and we made it BlueprintAssignable we can bind to this Delegate in Blueprints*/
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged; //FOnHealthChangedSignature is a delegate Type and OnHealthChanged is the delegate itself

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged; //FOnMaxHealthChangedSignature is a delegate Type and OnMaxHealthChanged is the delegate itself

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged; //FOnManaChangedSignature is a delegate Type and OnManaChanged is the delegate itself

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged; //FOnMaxManaChangedSignature is a delegate Type and OnMaxManaChanged is the delegate itself

protected:
	//NOTE: Here we are declaring the callback functions that will be called when the attributes (Ej. Health, MaxMana) change in the AttributeSet.
	void HealthChanged(const FOnAttributeChangeData& Data) const; //this function will be called when the Health attribute changes
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const; //this function will be called when the MaxHealth attribute changes
	void ManaChanged(const FOnAttributeChangeData& Data) const; //this function will be called when the Mana attribute changes, this is the callback function
	void MaxManaChanged(const FOnAttributeChangeData& Data) const; //this function will be called when the MaxMana attribute changes
};
