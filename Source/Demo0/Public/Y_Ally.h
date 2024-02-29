// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Character.h"
#include "Y_Ally.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API AY_Ally : public AY_Character
{
	GENERATED_BODY()
public:
	AY_Ally();

	virtual void BeginPlay() override;

	virtual void Attack();

	virtual void Injured();
};
