// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Equipment.h"

void L_I02();

class DEMO0_API NormalEQ : public Y_Equipment
{
public:
	virtual bool AcceptFloor(class AY_Floor* GetFloor);
};

//1-1 木剑：5D
class DEMO0_API EQ01 : public Y_Equipment
{
public:

	EQ01();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//1-2 铁剑：造成8伤害
class DEMO0_API EQ02 : public Y_Equipment
{
public:

	EQ02();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//1-3-1 制式钢剑：造成敌方当前生命值10%的伤害
class DEMO0_API EQ03 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ03();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//1-3-2 附魔剑：造成敌方已损失生命值10%的伤害
class DEMO0_API EQ04 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ04();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};


//2 - 1 功法书：抽2
class DEMO0_API EQ05 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ05();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//2-2 宗门手册：抽3
class DEMO0_API EQ06 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ06();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//2-3-1 百科全书： 抽至6
class DEMO0_API EQ07 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ07();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//2-3-2 应急宝典： 弃所有抽等同
class DEMO0_API EQ08 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ08();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//3-1 放血刀 1层【易伤】
class DEMO0_API EQ09 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ09();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//3-2 剔骨刀 1【易伤】1【虚弱】
class DEMO0_API EQ10 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ10();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//3-3-1 锯骨刀 2【易伤】2【虚弱】
class DEMO0_API EQ11 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ11();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//3-3-2 刺心刀 2【易伤】，易伤数值翻倍
class DEMO0_API EQ12 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ12();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//4-1 布甲 5S
class DEMO0_API EQ13 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ13();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//4-2 铁甲 8S
class DEMO0_API EQ14 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ14();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//4-3-1 寒铁甲 自身已损失生命值30%S
class DEMO0_API EQ15 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ15();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//4-3-2 陨铁甲 自身最大生命值20%S
class DEMO0_API EQ16 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ16();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//5-1 木盾 受到伤害减少3
class DEMO0_API EQ17 : public Y_Equipment
{
public:

	EQ17();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//5-2 铁盾 受到伤害减少5
class DEMO0_API EQ18 : public Y_Equipment
{
public:

	EQ18();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//5-3-1 附魔盾 不会受到10以下的伤害
class DEMO0_API EQ19 : public Y_Equipment
{
public:

	EQ19();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//5-3-2 制式钢盾 受到伤害减少25%
class DEMO0_API EQ20 : public Y_Equipment
{
public:

	EQ20();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//6-1 应急绷带 战斗结束+3H
class DEMO0_API EQ21 : public Y_Equipment
{
public:

	EQ21();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//6 - 2 跌打药 战斗结束 + 5H
class DEMO0_API EQ22 : public Y_Equipment
{
public:

	EQ22();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//6-3-1 大还丹 战斗结束+已损失20%H
class DEMO0_API EQ23 : public Y_Equipment
{
public:

	EQ23();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//6-3-2 补药 战斗结束+5H+5MaxH
class DEMO0_API EQ24 : public Y_Equipment
{
public:

	EQ24();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//7-1 诅咒剑 -5H，10D
class DEMO0_API EQ25 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ25();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//7-2 咒剑 -8D，15D
class DEMO0_API EQ26 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ26();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//7-3-1 饮血剑 8H，15D
class DEMO0_API EQ27 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ27();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//7-3-2 灵剑 -8D，除去【易伤】【虚弱】
class DEMO0_API EQ28 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ28();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};