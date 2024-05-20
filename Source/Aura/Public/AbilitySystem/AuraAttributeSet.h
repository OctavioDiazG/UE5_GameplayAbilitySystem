// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	/* Declare Attributes */
	/* Steps to create an Attribute
	 * 1. Declare the attribute in the header file.
	 *	- Start the declaration with FGameplayAttributeData
	 *  - Add the UPROPERTY specifier to the attribute
	 * 2. Is the attribute replicated? If so, add the ReplicatedUsing specifier.
	 *  - ReplicatedUsing = OnRep_AttributeName
	 * 3. Declare the OnRep function for the attribute.
	 *  - void OnRep_AttributeName(const FGameplayAttributeData& OldAttribute) const
	 *  - Don't forget to add UFUNCTION() specifier to the function
	 * 4. Implement the OnRep function in the cpp file
	 *  - GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, AttributeName, OldAttribute)
	 * 5. Declare the GetLifetimeReplicatedProps function in the header file
	 *  - virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	 *  - only add the attributes that needs to be replicated.
	 * 6. Implement the GetLifetimeReplicatedProps function in the cpp file
	 *  - DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, AttributeName, COND_None, REPNOTIFY_Always)
	 * 
	 */
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // This is needed to replicate attributes
	
#pragma region Health Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attibutes")
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attibutes")
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
#pragma endregion

#pragma region Mana Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attibutes")
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attibutes")
	FGameplayAttributeData MaxMana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
#pragma endregion

	
};


