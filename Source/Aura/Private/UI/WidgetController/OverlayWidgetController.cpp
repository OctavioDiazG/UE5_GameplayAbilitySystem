// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BrodCastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet); //Get the AttributeSet from the parent class (UAuraWidgetController) and cast it to UAuraAttributeSet

	//NOTE: Here we are broadcasting the initial values to the UI (OverlayWidget)
	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth()); //Broadcast the Health value to the UI
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth()); //Broadcast the MaxHealth value to the UI
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana()); //Broadcast the Mana value to the UI
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana()); //Broadcast the MaxMana value to the UI
}

void UOverlayWidgetController::BindCallBacksToDependencies() //this function will bind the callbacks to the dependencies
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet); //Get the AttributeSet from the parent class (UAuraWidgetController) and cast it to UAuraAttributeSet

	//NOTE: Here we are binding the callback functions to the attributes in the AttributeSet 
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged); //Bind the HealthChanged function to the Health Attribute
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged); //Bind the MaxHealthChanged function to the MaxHealth Attribute
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged); //Bind the ManaChanged function to the Mana Attribute
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged); //Bind the MaxManaChanged function to the MaxMana Attribute
	
}

#pragma region Callback Functions
//NOTE: Inside these functions we'll need some Delegate to broadcast the changes to the UI (Check the .h file)

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const //this function will be called when the Health attribute changes
{
	OnHealthChanged.Broadcast(Data.NewValue); //Broadcast the Health value to the UI
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const //this function will be called when the MaxHealth attribute changes
{
	OnMaxHealthChanged.Broadcast(Data.NewValue); //Broadcast the MaxHealth value to the UI
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const //this function will be called when the Mana attribute changes
{
	OnManaChanged.Broadcast(Data.NewValue); //Broadcast the Mana value to the UI
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const //this function will be called when the MaxMana attribute changes
{
	OnMaxManaChanged.Broadcast(Data.NewValue); //Broadcast the MaxMana value to the UI
}

#pragma endregion