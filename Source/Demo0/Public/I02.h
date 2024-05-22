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

//1-1 ľ����5D
class DEMO0_API EQ01 : public Y_Equipment
{
public:

	EQ01();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//1-2 ���������8�˺�
class DEMO0_API EQ02 : public Y_Equipment
{
public:

	EQ02();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//1-3-1 ��ʽ�ֽ�����ɵз���ǰ����ֵ10%���˺�
class DEMO0_API EQ03 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ03();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//1-3-2 ��ħ������ɵз�����ʧ����ֵ10%���˺�
class DEMO0_API EQ04 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ04();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};


//2 - 1 �����飺��2
class DEMO0_API EQ05 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ05();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//2-2 �����ֲ᣺��3
class DEMO0_API EQ06 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ06();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//2-3-1 �ٿ�ȫ�飺 ����6
class DEMO0_API EQ07 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ07();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//2-3-2 Ӧ�����䣺 �����г��ͬ
class DEMO0_API EQ08 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ08();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//3-1 ��Ѫ�� 1�㡾���ˡ�
class DEMO0_API EQ09 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ09();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//3-2 �޹ǵ� 1�����ˡ�1��������
class DEMO0_API EQ10 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ10();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//3-3-1 ��ǵ� 2�����ˡ�2��������
class DEMO0_API EQ11 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ11();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//3-3-2 ���ĵ� 2�����ˡ���������ֵ����
class DEMO0_API EQ12 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ12();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//4-1 ���� 5S
class DEMO0_API EQ13 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ13();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//4-2 ���� 8S
class DEMO0_API EQ14 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ14();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//4-3-1 ������ ��������ʧ����ֵ30%S
class DEMO0_API EQ15 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ15();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//4-3-2 ������ �����������ֵ20%S
class DEMO0_API EQ16 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ16();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//5-1 ľ�� �ܵ��˺�����3
class DEMO0_API EQ17 : public Y_Equipment
{
public:

	EQ17();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//5-2 ���� �ܵ��˺�����5
class DEMO0_API EQ18 : public Y_Equipment
{
public:

	EQ18();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//5-3-1 ��ħ�� �����ܵ�10���µ��˺�
class DEMO0_API EQ19 : public Y_Equipment
{
public:

	EQ19();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//5-3-2 ��ʽ�ֶ� �ܵ��˺�����25%
class DEMO0_API EQ20 : public Y_Equipment
{
public:

	EQ20();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//6-1 Ӧ������ ս������+3H
class DEMO0_API EQ21 : public Y_Equipment
{
public:

	EQ21();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//6 - 2 ����ҩ ս������ + 5H
class DEMO0_API EQ22 : public Y_Equipment
{
public:

	EQ22();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//6-3-1 �󻹵� ս������+����ʧ20%H
class DEMO0_API EQ23 : public Y_Equipment
{
public:

	EQ23();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//6-3-2 ��ҩ ս������+5H+5MaxH
class DEMO0_API EQ24 : public Y_Equipment
{
public:

	EQ24();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//7-1 ���佣 -5H��10D
class DEMO0_API EQ25 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ25();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//7-2 �佣 -8D��15D
class DEMO0_API EQ26 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ26();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//7-3-1 ��Ѫ�� 8H��15D
class DEMO0_API EQ27 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ27();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};

//7-3-2 �齣 -8D����ȥ�����ˡ���������
class DEMO0_API EQ28 : public Y_Equipment
{
public:
	int32 ELevel;

	EQ28();

	virtual void Play(bool Execute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};