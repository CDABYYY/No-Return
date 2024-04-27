// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Buff.h"
#include "Y_EnemyInfo.h"
#include "Y_CardInfo.h"
#include "Y_RoomWidget.h"
#include "Y_Floor.h"


/**
 * 
 */
void LoadY_Base();

class DEMO0_API MoveBuff:public Y_Buff
{
public:
	MoveBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
	virtual void AddToCharacter(class AY_Character* TargetCharacter,bool Execute)override;
	virtual FText printBuff(bool PrintLog = false)const override;
};

class DEMO0_API DemageBuff :public Y_Buff
{
public:
	DemageBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
	virtual void AddToCharacter(class AY_Character* TargetCharacter,bool Execute)override;
	virtual FText printBuff(bool PrintLog = false)const override;
};

class DEMO0_API ShieldBuff :public Y_Buff
{
public:
	ShieldBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
	virtual FText printBuff(bool PrintLog = false)const override;
};

class DEMO0_API BurnBuff :public Y_Buff
{
public:
	BurnBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
	virtual FText printBuff(bool PrintLog = false)const override;
};

class DEMO0_API NormalCard : public Y_CardInfo
{
public:
	NormalCard();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	virtual FText GetCardDescribe()override;
	virtual FText GetPointDescribe()override;
};

class DEMO0_API AttackAction : public Y_CharacterAction
{
public:
	AttackAction();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;

	virtual FText LogDescript()override;
};

class DEMO0_API NormalAction : public Y_CharacterAction
{
public:
	NormalAction();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;

	virtual FText LogDescript()override;
};

class DEMO0_API NormalEnemy : public Y_EnemyInfo
{
public:
	NormalEnemy();

	virtual void EnemyDead()override;
};

class DEMO0_API NormalRoom : public Y_RoomInfo
{
public:
	NormalRoom();

	virtual FText GetDescribe()override;

	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;

	virtual void LeaveRoom()override;

	virtual float GetWeight()override;
};

class DEMO0_API EventRoom : public Y_RoomInfo
{
public:
	EventRoom();

	virtual FText GetDescribe()override;

	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;

	virtual void LeaveRoom()override;
};

class DEMO0_API NormalFloor : public Y_FloorInfo
{
public:
	NormalFloor();

	virtual void Pass(class AY_Character* Character);

	virtual void Enter(class AY_Character* Character);

	virtual void Leave(class AY_Character* Character);
};

class DEMO0_API NormalSkill : public Y_CardInfo
{
public:
	NormalSkill();

	virtual void Play(bool Execute)override;
};