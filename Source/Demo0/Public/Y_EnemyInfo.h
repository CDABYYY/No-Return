// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_StatusBar.h"

/**
 * 
 */

class DEMO0_API Y_CharacterAction
{
public:
	Y_CharacterAction();
	virtual ~Y_CharacterAction() {};
	int32 OriginalCost;
	int32 CurrentCost;
	int32 ActionID;
	FName UsingMontageName;
	UTexture2D* UsingPicture;
	FText ActionDescribe;
	FText ActionName;
	float Weight = 0;

	class Y_EnemyInfo* OwnerEnemy;

	virtual class AY_Character* GetOwner();

	virtual int32 GetCost();

	virtual void Init(class Y_EnemyInfo* Owner);

	void ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ExecuteBuffs, bool TryExecute);

	void Move(int32 Distance, bool Execute);

	virtual float GetRate();

	virtual float GetWeight();

	virtual void ActionChoosed();

	virtual void ActionExecute();

	virtual FText LogDescript();

	virtual FText GetName();

	virtual FText GetDescribe();
};


class DEMO0_API Y_EnemyInfo
{
public:
	Y_EnemyInfo();
	virtual ~Y_EnemyInfo();

	virtual void Init(int32 Level);
	UTexture2D* EnemyProfile;
	int32 MaxHealth;
	int32 CurrentHealth;
	int32 EnemyLevel;
	TArray<TSharedPtr<Y_CharacterAction>> Actions;
	class AY_Character* Owner;

	int32 ActionType;
	int32 ActionValue;
	int32 ChoosedAction;

	int32 EnemyID;

	int32 GetRandomAction();

	virtual void EnemyAttack();

	virtual void EnemyDead();
};
