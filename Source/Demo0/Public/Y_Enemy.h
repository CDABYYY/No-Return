// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Character.h"
#include "Y_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API AY_Enemy : public AY_Character
{
	GENERATED_BODY()
public:
	AY_Enemy();

	virtual void Attack();

	virtual void Injured();

	UFUNCTION(BlueprintCallable)
	void ShortAttack();

	UFUNCTION(BlueprintCallable)
	void HardAttack();

	UFUNCTION(BlueprintCallable)
	void MoveMotion();

	TDelegate<void()> ReadyAttack;
};
