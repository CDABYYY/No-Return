// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_EnemyInfo.h"

class DEMO0_API GainBuff :public Y_Buff {
public:
	GainBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

class DEMO0_API SeriousBuff :public Y_Buff {
public:
	SeriousBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

class DEMO0_API MoraleBuff :public Y_Buff {
public:
	MoraleBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

class DEMO0_API OverBuff :public Y_Buff {
public:
	OverBuff();
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

class DEMO0_API S01 : public Y_CharacterAction//���ƶ�������5 �ƶ�1
{
public:
	S01();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S02 : public Y_CharacterAction//��˳ն������15 ��Χ1 �˺�4
{
public:
	S02();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S03 : public Y_CharacterAction//������������20 ��Χ2 �˺�6
{
public:
	S03();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S04 : public Y_CharacterAction//���Ʒ�������20 ��Χ1 �˺�4 ����2
{
public:
	S04();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S05 : public Y_CharacterAction//���������20 ��Χ1 �˺�4 ����2
{
public:
	S05();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S06 : public Y_CharacterAction//������������15 ��Χ4 �˺�8 �޷����
{
public:
	S06();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S07 : public Y_CharacterAction//������֧Ԯ������20 �ٻ�һ��ɽ��
{
public:
	S07();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S08 : public Y_CharacterAction//����桿����15 �ƶ���Χ2 �˺�4
{
public:
	S08();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S09 : public Y_CharacterAction//���̻�������15 ��Χ2 �˺�5
{
public:
	S09();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S10 : public Y_CharacterAction//���ػ�������20 ��Χ3 ����10
{
public:
	S10();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S11 : public Y_CharacterAction//���ܻ�������20 ��Χ1 �˺�5 ����1
{
public:
	S11();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S12 : public Y_CharacterAction//������������15 �˺�ÿ���ж��˺�+2
{
public:
	S12();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S13 : public Y_CharacterAction//����桿����15 �ƶ���Χ2 �˺�4
{
public:
	S13();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S14 : public Y_CharacterAction//���²С�����15 ��Χ1 �˺�5 ����1
{
public:
	S14();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S15 : public Y_CharacterAction//������������15 ��Χ1 3���˺�2
{
public:
	S15();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S16 : public Y_CharacterAction//�����ơ�����15 ����˺���1
{
public:
	S16();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S17 : public Y_CharacterAction//������������15 ��Χ1 3���˺�2 ����5
{
public:
	S17();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S18 : public Y_CharacterAction//�����ơ�����15 ����˺���1 ����5
{
public:
	S18();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S19 : public Y_CharacterAction//��ʹ��������15 ��Χ1 �˺�5 ����2
{
public:
	S19();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S20 : public Y_CharacterAction//���㲦������15 ��Χ3 �˺���1
{
public:
	S20();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S21 : public Y_CharacterAction//��Ѱ�����㡿����15 ��Χ3 �������¶��2
{
public:
	S21();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S22 : public Y_CharacterAction//����ѧ������30 �ٻ�һ������
{
public:
	S22();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S23 : public Y_CharacterAction//����桿����15 �ƶ���Χ3 �˺�5
{
public:
	S23();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S24 : public Y_CharacterAction//��ָ�㡿����15 ��Χ1 �˺�5 ����ƶ�������������
{
public:
	S24();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S25 : public Y_CharacterAction//���������ࡿ����20 ����20
{
public:
	S25();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S26 : public Y_CharacterAction//������������20 ��Χ2 3���˺�5
{
public:
	S26();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S27 : public Y_CharacterAction//���²С�����20 ��Χ2 �˺�8 ����2
{
public:
	S27();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S28 : public Y_CharacterAction//���ս᡿����25 ��Χ4 �˺�40
{
public:
	S28();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S29 : public Y_CharacterAction//�������˿ڡ�����20 ��Χ1 �˺�10 ����2
{
public:
	S29();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S30 : public Y_CharacterAction//�����ˡ�����20 ��Χ1 �˺�10 ��Ѫ2
{
public:
	S30();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S31 : public Y_CharacterAction//�������ֽ����20 ��Χ1 �˺�15 ����2
{
public:
	S31();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S32 : public Y_CharacterAction//�����塿����15 ����ƶ�����2�š����ǡ�
{
public:
	S32();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S33 : public Y_CharacterAction//��ʹ��������20 ��Χ2 �˺�20
{
public:
	S33();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S34 : public Y_CharacterAction//������������20 ���е�������˺���1
{
public:
	S34();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S35 : public Y_CharacterAction//������������20 ���е��˻�û���10
{
public:
	S35();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S36 : public Y_CharacterAction//��ͻ�̡�����15 �ƶ���Χ3 �˺�10
{
public:
	S36();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S37 : public Y_CharacterAction//���ػ�������15 ��Χ3 ����һ���˻�û���15
{
public:
	S37();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S38 : public Y_CharacterAction//��ף��������15 ��Χ3 ����һ���˻������2 �ظ�Ѫ��15
{
public:
	S38();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S39 : public Y_CharacterAction//������������15 ��Χ4 �˺�8 �޷����
{
public:
	S39();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S40 : public Y_CharacterAction//���������򡿻���15 ��Χ2 ����10 �˺�15
{
public:
	S40();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S41 : public Y_CharacterAction//��ͻ�̡�����15 ��Χ3 �˺�15 ����1
{
public:
	S41();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S42 : public Y_CharacterAction//������Ԯ��������30 �ٻ���������
{
public:
	S42();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S43 : public Y_CharacterAction//��ͻ�̡�����20 �ƶ���Χ3 �˺�15
{
public:
	S43();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;

};

class DEMO0_API S44 : public Y_CharacterAction//������������20 �˺�+5
{
public:
	S44();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S45 : public Y_CharacterAction//������������20 ��Χ4 �˺�15 ��������
{
public:
	S45();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S46 : public Y_CharacterAction//�����롿����20 ��Χ1 �˺�10 �����1��
{
public:
	S46();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S47 : public Y_CharacterAction//������������20 �˺�+5
{
public:
	S47();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S48 : public Y_CharacterAction//������������15 ��Χ1 3���˺�10
{
public:
	S48();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S49 : public Y_CharacterAction//������������15 ��Χ2 2���˺�10
{
public:
	S49();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S50 : public Y_CharacterAction//��ͻ�̡�����20 �ƶ���Χ3 �˺�10
{
public:
	S50();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S51 : public Y_CharacterAction//������������20 �˺�+5
{
public:
	S51();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S52 : public Y_CharacterAction//����Ϣ������20 �˺�+2 �ظ�Ѫ��20
{
public:
	S52();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S53 : public Y_CharacterAction//������������20 ��������ˡ��������� �˺�+2
{
public:
	S53();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S54 : public Y_CharacterAction//������������20 3�Σ��ƶ�2 �˺�10��
{
public:
	S54();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S55 : public Y_CharacterAction//���²С�����20 ��Χ3 �˺�15 ����2
{
public:
	S55();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S56 : public Y_CharacterAction//��ͻ�̡�����20 �ƶ���Χ3 �˺�15
{
public:
	S56();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S57 : public Y_CharacterAction//��ɨ��������20 ��Χ2 2���˺�10
{
public:
	S57();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S58 : public Y_CharacterAction//������������15 ��Χ4 �˺�10 �޷�����
{
public:
	S58();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S59 : public Y_CharacterAction//���ָ�������15 ��Χ3 ���Ŀ�꡾���ˡ���������
{
public:
	S59();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S60 : public Y_CharacterAction//���ӻ�������20 ��Χ1 ������Ŀ���û���15
{
public:
	S60();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S61 : public Y_CharacterAction//������ʿ��������15 ʿ��+5
{
public:
	S61();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S62 : public Y_CharacterAction//��ҫ�䡿����15 �����ѷ���á����桿2
{
public:
	S62();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S63 : public Y_CharacterAction//���ػ�������15 ��Χ2 3���˺�10
{
public:
	S63();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S64 : public Y_CharacterAction//��ͻ�̡�����20 �ƶ�3 �˺�15 �����ˡ�1
{
public:
	S64();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S65 : public Y_CharacterAction//�������˿ڡ�����20 ��Χ3 �˺�15 �����ˡ�3
{
public:
	S65();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S66 : public Y_CharacterAction//������������20 ��Χ2 2*���˺�10 �����ˡ�1��
{
public:
	S66();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S67 : public Y_CharacterAction//�����ˡ�����15 ��Χ4 �˺�5 �����ˡ�2 �޷����
{
public:
	S67();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S68 : public Y_CharacterAction//������������15 ��Χ4 �˺�5 ��������2 �޷����
{
public:
	S68();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S69 : public Y_CharacterAction//������������15 ��Χ4 3*���˺�5 �����ˡ�2���޷����
{
public:
	S69();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S70 : public Y_CharacterAction//�����衿����20 �ѷ���ɫ��õ�ͬ���ǡ����ˡ����Ļ��� �޷����
{
public:
	S70();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S71 : public Y_CharacterAction//�����ˡ�����20 ��Χ4 �˺�10�����ˡ�1 ����ÿ��5�㡾���ˡ�����1�š�ʹ�ࡿ �޷����
{
public:
	S71();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S72 : public Y_CharacterAction//��Զ�롿����10 ��Χ1 �˺�10 �����ˡ�1 �����1�� �޷����
{
public:
	S72();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S73 : public Y_CharacterAction//����桿����15 �ƶ���Χ3 �˺�15 �����ء�-1
{
public:
	S73();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S74 : public Y_CharacterAction//�����ع���������15 ��Χ2 �˺�15 ����10 �����ء�-2
{
public:
	S74();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S75 : public Y_CharacterAction//��ͻϮ������15 �ƶ���Χ4 �˺�10 �����ء�-2
{
public:
	S75();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S76 : public Y_CharacterAction//�����ع���������15 ��Χ2 2*���˺�10�������ء�-2
{
public:
	S76();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S77 : public Y_CharacterAction//�����롿����15 ��Χ1 �˺�10 ����ƶ�2��
{
public:
	S77();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/

class DEMO0_API S78 : public Y_CharacterAction//����ս���ˡ�����20 �����ѷ�+3�����ء�
{
public:
	S78();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S79 : public Y_CharacterAction//������֧Ԯ������30 �ٻ�1��������
{
public:
	S79();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S80 : public Y_CharacterAction//���ӹ̷���������20 �����ѷ�+20S
{
public:
	S80();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S81 : public Y_CharacterAction//�����ҹ���������20 �����ѷ�+3�˺�
{
public:
	S81();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

/***************************************************************************************/