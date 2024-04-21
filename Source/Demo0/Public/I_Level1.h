// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Y_CardInfo.h"

void IL1();

class DEMO0_API I_C01 :public Y_CardInfo//花费3 伤害5（敌） 范围1
{
public:
	I_C01();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C02 :public Y_CardInfo//花费3 护盾6（自）
{
public:
	I_C02();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C03 :public Y_CardInfo//花费2 抽卡3 灼烧2（自）
{
public:
	I_C03();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C04 :public Y_CardInfo//花费4 移动2 灼烧2（自）
{
public:
	I_C04();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C05 :public Y_CardInfo//花费3 灼烧4（敌） 范围2
{
public:
	I_C05();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C06 :public Y_CardInfo//花费4 灼烧5（全） 范围2 AOE2
{
public:
	I_C06();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C07 :public Y_CardInfo//花费4 伤害【灼层】/2（自） 护盾【灼层】（自）
{
public:
	I_C07();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C08 :public Y_CardInfo//花费4 范围0 AOE3 伤害【灼层】（全）
{
public:
	I_C08();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C09 :public Y_CardInfo//花费5 一名角色维持【灼层】3/4 (待完善)
{
public:
	I_C09();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C10 :public Y_CardInfo//花费5 灼烧4（自） 清除负面状态L5-
{
public:
	I_C10();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C11 :public Y_CardInfo//花费5 移动4 灼烧3（敌）
{
public:
	I_C11();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C12 :public Y_CardInfo//花费5 抽卡1 (待完善)
{
public:
	I_C12();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C13 :public Y_CardInfo//花费3 灼烧【灼层】（敌）
{
public:
	I_C13();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C14 :public Y_CardInfo//花费5 攻击附带灼烧2 (待完善)
{
public:
	I_C14();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C15 :public Y_CardInfo//花费3 抽卡【灼层】/3
{
public:
	I_C15();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C16 :public Y_CardInfo//花费4 （伤害2 灼烧1）*3
{
public:
	I_C16();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C17 :public Y_CardInfo//花费2 护盾【灼层】
{
public:
	I_C17();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C18 :public Y_CardInfo//花费6 移动3 每移动1减少【灼层】1 (待完善)
{
public:
	I_C18();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C19 :public Y_CardInfo//花费2 结算并清除所有【灼层】 （待完善）
{
public:
	I_C19();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};

class DEMO0_API I_C20 :public Y_CardInfo//结算时全场【灼层】加1 （待完善）
{
public:
	I_C20();
	virtual FText LogDescript()override;
	virtual void Play()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
};
