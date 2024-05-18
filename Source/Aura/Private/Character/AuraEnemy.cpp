// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"


void AAuraEnemy::HighlightActor()
{
	//Draw a debug Sphere
	DrawDebugSphere(GetWorld(), GetActorLocation(), 100.0f, 12, FColor::Green, false, 2.0f);
}

void AAuraEnemy::UnhighlightActor()
{
	//Remove the debug Sphere
	DrawDebugSphere(GetWorld(), GetActorLocation(), 100.0f, 12, FColor::Green, false, 0.0f);
}
