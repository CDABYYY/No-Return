// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_StatusBar.h"

/**
 *
 */

class DEMO0_API Y_CharacterAction : public TSharedFromThis<Y_CharacterAction>
{
public:
	Y_CharacterAction();
	virtual ~Y_CharacterAction() {};
	int32 ActionID;
	FText ActionDescribe;
	FText ActionName;

	int32 OriginalCost;
	int32 CurrentCost;
	FName UsingMontageName;
	UTexture2D* UsingPicture;
	float Weight = 0;

	class Y_EnemyInfo* OwnerEnemy;

	virtual class AY_Character* GetOwner();

	virtual int32 GetCost();

	virtual void Init(class Y_EnemyInfo* Owner);

	//Nullptr 将被视作无来源伤害，非Nullptr的指针如果指向对象不存在则停止执行
	virtual void ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ExecuteBuffs, bool TryExecute);

	virtual void Move(int32 Distance, bool Execute);

	virtual void BindMessage(FString Name);

	virtual float GetRate();

	virtual float GetWeight();

	virtual void ActionChoosed();

	virtual void ActionExecute(bool Execute);

	virtual bool AttackFloor(class AY_Floor* TargetFloor);

	virtual bool CanAttackFloor(class AY_Floor* TargetFloor);

	virtual void PlayMontage(FName MontageName, class AY_Floor* ChoosedFloor = nullptr, float PlayRate = 0);

	virtual void PlayMontage(bool Execute, class AY_Floor* ChoosedFloor = nullptr, float PlayRate = 0);

	virtual void PlayMontage(bool Execute, int32 ToPosition = 0, float PlayRate = 0);

	virtual void PlayNiagara(bool Execute, FName PlayName, class AY_Floor* FromFloor, class AY_Floor* ToFloor, float Duration = 1);

	virtual void PlayNiagara(bool Execute, FName PlayName, class AY_Floor* FromFloor, int32 Distance, float Duration = 1);

	virtual FText LogDescript();

	virtual FText GetName();

	virtual FText GetDescribe();

	virtual UTexture2D* GetPicture();
};


class DEMO0_API Y_EnemyInfo :public TSharedFromThis<class Y_EnemyInfo>
{
public:
	Y_EnemyInfo();
	virtual ~Y_EnemyInfo();

	virtual void Init(int32 Level);
	FName BindBlueprint;
	FText EnemyName;
	UTexture2D* EnemyProfile;
	int32 MaxHealth;
	int32 CurrentHealth;
	int32 EnemyLevel;
	TArray<TSharedPtr<Y_CharacterAction>> Actions;
	class AY_Character* Owner;

	int32 ActionType;
	int32 ActionValue;
	int32 ChoosedAction;
	int32 ActionCount;

	int32 AttackEnhance;

	int32 EnemyID;

	int32 GetRandomAction();

	virtual void EnemyAttack();

	virtual void EnemyDead();

	virtual void LoadCharacter(AY_Character* NewOwner);

	virtual void ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ExecuteBuffs, bool TryExecute = true);
};
