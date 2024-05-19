// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include "Player/AuraPlayerState.h"


AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent"); // Create the ability system component
	AbilitySystemComponent->SetIsReplicated(true); // Set the ability system component to be replicated
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); // Set the replication mode of the ability system component to minimal because we don't need to replicate all the gameplay effects to the client just GamplayCues and the attributes

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet"); // Create the attribute set
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
