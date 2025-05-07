// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // Getter for the ability system component
	UAttributeSet* GetAttributeSet() const { return AttributeSet; } // Getter for the attribute set

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat") // Edit anywhere in the combat category
	TObjectPtr<USkeletalMeshComponent> Weapon; //skeletal mesh component for the weapon

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent; // Ability system component
 
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet; // Attribute set
	

	

};
