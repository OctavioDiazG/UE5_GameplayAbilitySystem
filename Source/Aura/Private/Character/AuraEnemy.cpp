// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // Set the collision response of the mesh to block visibility
	
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); // Set the custom depth stencil value of the mesh to red, we don't set it on HighlightActor because it would be redundant to set it every time we highlight the actor
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); // Same as above but for the weapon

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent"); // Create the ability system component
	AbilitySystemComponent->SetIsReplicated(true); // Set the ability system component to be replicated
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // Set the replication mode of the ability system component to minimal because we don't need to replicate all the gameplay effects to the client just GamplayCues and the attributes

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet"); // Create the attribute set
	
	


	
}

void AAuraEnemy::HighlightActor()
{
	//Draw a debug Sphere
	GetMesh()->SetRenderCustomDepth(true); // Set the mesh to render custom depth
	//GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); 
	Weapon->SetRenderCustomDepth(true); // Set the weapon to render custom depth
	//Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnhighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false); // Set the mesh to not render custom depth
	Weapon->SetRenderCustomDepth(false); // Set the weapon to not render custom depth
	
}
