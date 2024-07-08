// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot")); // Create a scene root component
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Get the ability system component of the target actor, if the Actor does not implement the UAbilitySystemComponent, this same function will look for a component in the actor that has a UAbilitySystemComponent
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (TargetASC == nullptr) return; // If the target actor doesn't have an ability system component, return

	check(GameplayEffectClass); // Check if the GameplayEffectClass is valid, if the actor does not have a valid UAbilitySystemComponent, the engine will crash
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext(); // Create an effect context handle
	EffectContextHandle.AddSourceObject(this);  // Add the source object to the effect context handle
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle); // Create a gameplay effect spec handle
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()); // Apply the gameplay effect to the target actor, need to pass the data of the effect spec handle. the * is used to dereference the data of the effect spec handle because the ApplyGameplayEffectSpecToSelf function expects a FGameplayEffectSpecHandle object, not a FGameplayEffectSpecHandle pointer
}


