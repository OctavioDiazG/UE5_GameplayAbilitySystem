// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget; // this is the overlay widget that we are going to create

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams); // this is the function that we are going to use to get the overlay widget controller

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS); // this is the function that we are going to use to initialize the overlay

protected:

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass; // this is the class that we are going to use to create the overlay widget

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController; // this is the overlay widget controller that we are going to create
	 
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass; // this is the class that we are going to use to create the overlay widget controller
};
