﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();

	//~ Begin Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	//~ End Enemy Interface

protected:

	virtual void BeginPlay() override;
	
};
