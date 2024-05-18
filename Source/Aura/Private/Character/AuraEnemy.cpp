// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh() -> SetVisibility(true);
	GetMesh() -> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAuraEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsHighlighted)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), 100.0f, 12, FColor::Green, false, -1.0f);
	}
}

void AAuraEnemy::HighlightActor()
{
	//Draw a debug Sphere
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 100.0f, 12, FColor::Green, false, 2.0f);
	bIsHighlighted = true;
}

void AAuraEnemy::UnhighlightActor()
{
	//Remove the debug Sphere
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 100.0f, 12, FColor::Green, false, 0.0f);
	bIsHighlighted = false;
}
