// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#pragma region GameplayAttributeData
/** ATTRIBUTE_ACCESSORS: the creator of accessors functions for attributes
     * This defines a set of helper functions for accessing and initializing attributes, to avoid having to manually write these functions.
     * It would create the following functions, for attribute Health
     *
     *	static FGameplayAttribute UMyHealthSet::GetHealthAttribute(); // Returns the FGameplayAttribute for Health
     *	FORCEINLINE float UMyHealthSet::GetHealth() const; // Returns the current value of Health
     *	FORCEINLINE void UMyHealthSet::SetHealth(float NewVal); // Sets the current value of Health
     *	FORCEINLINE void UMyHealthSet::InitHealth(float NewVal); // Sets the default value of Health
     *
     * To use this in your game you can define something like this, and then add game-specific functions as necessary:
     * 
     *	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
     *	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
     *	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
     *	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
     *	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
     * 
     *	ATTRIBUTE_ACCESSORS(UMyHealthSet, Health) // the parameters are the class name in this case UAuraAttributeSet and the attribute name
     */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
#pragma endregion

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	/* Declare Attributes
	 * Steps to create an Attribute
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
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attibutes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
#pragma endregion

#pragma region Mana Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attibutes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attibutes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
#pragma endregion

	
};


