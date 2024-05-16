// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon")); // Create a new skeletal mesh component
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponHandSocket")); // Attach the weapon to the mesh in the WeaponHandSocket Name
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Disable collision of the weapon Component

}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}