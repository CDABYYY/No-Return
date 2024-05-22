// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Buff.h"
#include "Y_EnemyInfo.h"
#include "Y_CardInfo.h"
#include "Y_RoomWidget.h"
#include "Y_Equipment.h"
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

class DEMO0_API PureDemageBuff :public Y_Buff {
public:
	PureDemageBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
	virtual void AddToCharacter(class AY_Character* TargetCharacter, bool Execute)override;
};

//ID 31
class DEMO0_API DemageBuff :public PureDemageBuff
{
public:
	DemageBuff();
};

//ID 32
class DEMO0_API BurnDemageBuff :public PureDemageBuff
{
public:
	BurnDemageBuff();
};

class DEMO0_API ShieldBuff :public Y_Buff
{
public:
	ShieldBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
	virtual FText printBuff(bool PrintLog = false)const override;
};

//ID 5, P[0]  £≤„∞Ÿ∑÷±»£¨ P[1] …À∫¶±∂ ˝
class DEMO0_API BurnBuff :public Y_Buff
{
public:
	BurnBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
	virtual FText printBuff(bool PrintLog = false)const override;
	virtual void AddToCharacter(class AY_Character* TargetCharacter, bool Execute)override;
	virtual void RemoveFromCharacter()override;
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

class DEMO0_API NormalEquipment : public Y_Equipment
{
public:
	int32 ELevel;

	NormalEquipment();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

class DEMO0_API WeakBuff :public Y_Buff {
public:
	WeakBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

class DEMO0_API ExposeBuff :public Y_Buff {
public:
	ExposeBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

class DEMO0_API NormalFightRoom : public Y_RoomInfo {
public:
	NormalFightRoom();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//ID 8 ∂ÓÕ‚ ‹µΩ1≤„B
class DEMO0_API OnBurnBuff :public Y_Buff {
public:
	OnBurnBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

//ID 9 ◊∆…’…À∫¶∑≠±∂
class DEMO0_API MoreBurnBuff :public Y_Buff {
public:
	MoreBurnBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
	virtual void AddToCharacter(class AY_Character* TargetCharacter, bool Execute);
	virtual void RemoveFromCharacter()override;
};

class DEMO0_API HealthBuff :public Y_Buff {
public:
	HealthBuff();
	virtual void AddToCharacter(class AY_Character* TargetCharacter, bool Execute);
};

class DEMO0_API NormalBossRoom :public Y_RoomInfo {
public:
	int32 BossType = 0;
	NormalBossRoom(int32 FinalBossType);

	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;

	virtual void LeaveRoom()override;
};