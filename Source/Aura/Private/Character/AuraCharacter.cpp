// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"


// Sets default values
AAuraCharacter::AAuraCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
}



// Called when the game starts or when spawned
void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AAuraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor info for the server
	InitAbilityActorInfo();
	
}



void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	//Init ability actor info for the client
	InitAbilityActorInfo();
}



// Called to bind functionality to input
void AAuraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); // Get the player state, is included in the include section of cpp file 
	check(AuraPlayerState); // Check if the player state is valid
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this); // Initialize the ability actor info which AuraPlayerState is the owner of the ability system component and this is the actor
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent(); // Set the ability system component to the player state ability system component
	AttributeSet = AuraPlayerState->GetAttributeSet(); // Set the attribute set to the player state attribute set

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController())) // place an if to get the PlayerController because in multiplayer games in client side the other player controllers are not valid if you are not the server.
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD())) // Get the HUD from the player controller
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet); // Initialize the overlay
		}
	}
	
}

