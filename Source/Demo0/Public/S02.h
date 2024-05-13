// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Y_CardInfo.h"

void LS02();

class DEMO0_API BornOFBuff :public Y_Buff {
public:
	BornOFBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

class DEMO0_API C45 :public Y_CardInfo//花费5 抽卡5 灼烧2（自）
{
public:
	C45();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C46 :public Y_CardInfo//花费5 抽卡【灼层】/2
{
public:
	C46();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C47 :public Y_CardInfo//花费5 护盾8（自） 灼烧2（自）
{
public:
	C47();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C48 :public Y_CardInfo//花费5 灼烧3（自） 清除自身【虚弱】【易伤】
{
public:
	C48();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C49 :public Y_CardInfo//花费5 灼烧3（自） 移动3 灼烧3（敌）【冲锋】
{
public:
	C49();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C50 :public Y_CardInfo//花费5 伤害【灼层】/2（自） 护盾【灼层】（自）
{
public:
	C50();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C51 :public Y_CardInfo//花费5 灼烧{受到的伤害}（自）
{
public:
	C51();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C52 :public Y_CardInfo//花费5 护盾{自身灼烧层数}（自）
{
public:
	C52();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C53 :public Y_CardInfo//花费5 范围2 AOE 伤害{自身灼烧层数}（自）
{
public:
	C53();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C54 :public Y_CardInfo//花费3 灼烧2（自） 弃去手牌并抽取等量的牌
{
public:
	C54();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C55 :public Y_CardInfo//花费5 移动1+【灼层】/3 灼烧1+【灼层】/3（敌）
{
public:
	C55();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C56 :public Y_CardInfo//花费10 护盾15（自）
{
public:
	C56();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C57 :public Y_CardInfo//花费10 防止伤害 向选中方向一格 伤害5*【灼层】（敌）
{
public:
	C57();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C58 :public Y_CardInfo//花费5 移动3 对目标和自身灼烧5
{
public:
	C58();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C59 :public Y_CardInfo//花费5 结算并清除自身【灼层】
{
public:
	C59();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C60 :public Y_CardInfo//花费10 在灼烧结算前 范围1 向敌人施加灼烧{自身【灼层】/2}
{
public:
	C60();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C61 :public Y_CardInfo//花费10 每受到3点灼烧抽1张牌
{
public:
	C61();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C62 :public Y_CardInfo//花费10 造成灼烧n时自身附加灼烧n/5
{
public:
	C62();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C63 :public Y_CardInfo//花费10 在受到灼烧伤害前获得自身【灼层】/2的护盾
{
public:
	C63();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C64 :public Y_CardInfo//花费10 当自身灼层大于8时，普通攻击附带1层灼烧
{
public:
	C64();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C65 :public Y_CardInfo//花费10 自身灼层大于10时，每次获得灼烧时触发【烈火矛身】效果
{
public:
	C65();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C66 :public Y_CardInfo//花费10 当自身灼层大于10时，每次攻击后全场获得1层灼烧
{
public:
	C66();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};

class DEMO0_API C67 :public Y_CardInfo//花费5 抽卡至6张
{
public:
	C67();
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;


};