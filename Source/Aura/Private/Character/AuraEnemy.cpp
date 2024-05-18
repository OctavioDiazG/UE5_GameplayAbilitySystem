// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // Set the collision response of the mesh to block visibility
	
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); // Set the custom depth stencil value of the mesh to red, we don't set it on HighlightActor because it would be redundant to set it every time we highlight the actor
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); // Same as above but for the weapon
}

/*
void AAuraEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsHighlighted)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), 100.0f, 12, FColor::Green, false, -1.0f);
	}
}*/

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
