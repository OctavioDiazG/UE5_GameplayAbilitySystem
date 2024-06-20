// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallBacksToDependencies();

		//return OverlayWidgetController;
	} // if the overlay widget controller is not null, we are going to set the widget controller params and return the overlay widget controller
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{ // this function is going to be called by the game mode to initialize the overlay

	checkf(OverlayWidgetClass, TEXT("OverlayWidgetController is UNINITIALIZED, Please set the OverlayWidgetControllerClass in the editor BP_AuraHUD class."));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is UNINITIALIZED, Please set the OverlayWidgetControllerClass in the editor BP_AuraHUD class."));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass); // we are going to create the overlay widget
	OverlayWidget = Cast<UAuraUserWidget>(Widget); // we are going to cast the widget to the overlay widget
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS); // we are going to create the widget controller params
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams); // we are going to get the overlay widget controller

	OverlayWidget->SetWidgetController(WidgetController); // we are going to set the widget controller

	WidgetController->BrodCastInitialValues(); // we are going to broadcast the initial values to the UI (OverlayWidget) REMEMBER THIS SHOULD BE CALLED AFTER THE WIDGET CONTROLLER IS SET
	
	Widget-> AddToViewport(); // we are going to add the widget to the viewport
	
}

