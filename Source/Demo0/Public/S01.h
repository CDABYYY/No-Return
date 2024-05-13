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

class DEMO0_API S01 : public Y_CharacterAction//【移动】花费5 移动1
{
public:
	S01();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S02 : public Y_CharacterAction//【顺斩】花费15 范围1 伤害4
{
public:
	S02();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S03 : public Y_CharacterAction//【劈砍】花费20 范围2 伤害6
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

class DEMO0_API S04 : public Y_CharacterAction//【破防】花费20 范围1 伤害4 易伤2
{
public:
	S04();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S05 : public Y_CharacterAction//【挑筋】花费20 范围1 伤害4 虚弱2
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

class DEMO0_API S06 : public Y_CharacterAction//【攻击】花费15 范围4 伤害8 无法躲避
{
public:
	S06();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S07 : public Y_CharacterAction//【请求支援】花费20 召唤一个山贼
{
public:
	S07();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S08 : public Y_CharacterAction//【冲锋】花费15 移动范围2 伤害4
{
public:
	S08();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S09 : public Y_CharacterAction//【刺击】花费15 范围2 伤害5
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

class DEMO0_API S10 : public Y_CharacterAction//【守护】花费20 范围3 护盾10
{
public:
	S10();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S11 : public Y_CharacterAction//【盾击】花费20 范围1 伤害5 虚弱1
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

class DEMO0_API S12 : public Y_CharacterAction//【蓄力】花费15 此后每次行动伤害+2
{
public:
	S12();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S13 : public Y_CharacterAction//【冲锋】花费15 移动范围2 伤害4
{
public:
	S13();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S14 : public Y_CharacterAction//【致残】花费15 范围1 伤害5 易伤1
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

class DEMO0_API S15 : public Y_CharacterAction//【连击】花费15 范围1 3次伤害2
{
public:
	S15();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S16 : public Y_CharacterAction//【架势】花费15 造成伤害加1
{
public:
	S16();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S17 : public Y_CharacterAction//【连击】花费15 范围1 3次伤害2 护盾5
{
public:
	S17();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S18 : public Y_CharacterAction//【架势】花费15 造成伤害加1 护盾5
{
public:
	S18();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S19 : public Y_CharacterAction//【痛击】花费15 范围1 伤害5 易伤2
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

class DEMO0_API S20 : public Y_CharacterAction//【点拨】花费15 范围3 伤害加1
{
public:
	S20();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S21 : public Y_CharacterAction//【寻找弱点】花费15 范围3 【弱点揭露】2
{
public:
	S21();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S22 : public Y_CharacterAction//【教学】花费30 召唤一名弟子
{
public:
	S22();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S23 : public Y_CharacterAction//【冲锋】花费15 移动范围3 伤害5
{
public:
	S23();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S24 : public Y_CharacterAction//【指点】花费15 范围1 伤害5 向抽牌堆塞入两张疑虑
{
public:
	S24();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S25 : public Y_CharacterAction//【调整节奏】花费20 护盾20
{
public:
	S25();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S26 : public Y_CharacterAction//【连击】花费20 范围2 3次伤害5
{
public:
	S26();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S27 : public Y_CharacterAction//【致残】花费20 范围2 伤害8 易伤2
{
public:
	S27();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S28 : public Y_CharacterAction//【终结】花费25 范围4 伤害40
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

class DEMO0_API S29 : public Y_CharacterAction//【扩大伤口】花费20 范围1 伤害10 易伤2
{
public:
	S29();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S30 : public Y_CharacterAction//【划伤】花费20 范围1 伤害10 流血2
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

class DEMO0_API S31 : public Y_CharacterAction//【挑断手筋】花费20 范围1 伤害15 虚弱2
{
public:
	S31();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S32 : public Y_CharacterAction//【威慑】花费15 向抽牌堆塞入2张【疑虑】
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

class DEMO0_API S33 : public Y_CharacterAction//【痛击】花费20 范围2 伤害20
{
public:
	S33();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S34 : public Y_CharacterAction//【增幅】花费20 所有敌人造成伤害加1
{
public:
	S34();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S35 : public Y_CharacterAction//【激励】花费20 所有敌人获得护盾10
{
public:
	S35();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S36 : public Y_CharacterAction//【突刺】花费15 移动范围3 伤害10
{
public:
	S36();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S37 : public Y_CharacterAction//【守护】花费15 范围3 与另一敌人获得护盾15
{
public:
	S37();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S38 : public Y_CharacterAction//【祝福】花费15 范围3 与另一敌人获得增益2 回复血量15
{
public:
	S38();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S39 : public Y_CharacterAction//【攻击】花费15 范围4 伤害8 无法躲避
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

class DEMO0_API S40 : public Y_CharacterAction//【连挡带打】花费15 范围2 护盾10 伤害15
{
public:
	S40();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S41 : public Y_CharacterAction//【突刺】花费15 范围3 伤害15 易伤1
{
public:
	S41();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S42 : public Y_CharacterAction//【请求援助】花费30 召唤辅助卫兵
{
public:
	S42();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S43 : public Y_CharacterAction//【突刺】花费20 移动范围3 伤害15
{
public:
	S43();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;

};

class DEMO0_API S44 : public Y_CharacterAction//【欢呼】花费20 伤害+5
{
public:
	S44();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S45 : public Y_CharacterAction//【攻击】花费20 范围4 伤害15 不可闪避
{
public:
	S45();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S46 : public Y_CharacterAction//【脱离】花费20 范围1 伤害10 向后退1格
{
public:
	S46();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S47 : public Y_CharacterAction//【欢呼】花费20 伤害+5
{
public:
	S47();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S48 : public Y_CharacterAction//【攻击】花费15 范围1 3次伤害10
{
public:
	S48();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S49 : public Y_CharacterAction//【攻击】花费15 范围2 2次伤害10
{
public:
	S49();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S50 : public Y_CharacterAction//【突刺】花费20 移动范围3 伤害10
{
public:
	S50();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S51 : public Y_CharacterAction//【欢呼】花费20 伤害+5
{
public:
	S51();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S52 : public Y_CharacterAction//【休息】花费20 伤害+2 回复血量20
{
public:
	S52();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S53 : public Y_CharacterAction//【爆发】花费20 清除【易伤】【虚弱】 伤害+2
{
public:
	S53();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S54 : public Y_CharacterAction//【征服】花费20 3次（移动2 伤害10）
{
public:
	S54();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S55 : public Y_CharacterAction//【致残】花费20 范围3 伤害15 易伤2
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

class DEMO0_API S56 : public Y_CharacterAction//【突刺】花费20 移动范围3 伤害15
{
public:
	S56();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S57 : public Y_CharacterAction//【扫荡】花费20 范围2 2次伤害10
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

class DEMO0_API S58 : public Y_CharacterAction//【攻击】花费15 范围4 伤害10 无法闪避
{
public:
	S58();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S59 : public Y_CharacterAction//【恢复】花费15 范围3 清除目标【易伤】【虚弱】
{
public:
	S59();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S60 : public Y_CharacterAction//【庇护】花费20 范围1 自身与目标获得护盾15
{
public:
	S60();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

/***************************************************************************************/

class DEMO0_API S61 : public Y_CharacterAction//【提振士气】花费15 士气+5
{
public:
	S61();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S62 : public Y_CharacterAction//【耀武】花费15 所有友方获得【增益】2
{
public:
	S62();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S63 : public Y_CharacterAction//【重击】花费15 范围2 3次伤害10
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

class DEMO0_API S64 : public Y_CharacterAction//【突刺】花费20 移动3 伤害15 【重伤】1
{
public:
	S64();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S65 : public Y_CharacterAction//【挑开伤口】花费20 范围3 伤害15 【重伤】3
{
public:
	S65();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S66 : public Y_CharacterAction//【连击】花费20 范围2 2*（伤害10 【重伤】1）
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

class DEMO0_API S67 : public Y_CharacterAction//【易伤】花费15 范围4 伤害5 【易伤】2 无法躲避
{
public:
	S67();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S68 : public Y_CharacterAction//【虚弱】花费15 范围4 伤害5 【虚弱】2 无法躲避
{
public:
	S68();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S69 : public Y_CharacterAction//【攻击】花费15 范围4 3*（伤害5 【重伤】2）无法躲避
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

class DEMO0_API S70 : public Y_CharacterAction//【鼓舞】花费20 友方角色获得等同主角【重伤】数的护盾 无法躲避
{
public:
	S70();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S71 : public Y_CharacterAction//【重伤】花费20 范围4 伤害10【重伤】1 主角每有5层【重伤】则获得1张【痛苦】 无法躲避
{
public:
	S71();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S72 : public Y_CharacterAction//【远离】花费10 范围1 伤害10 【重伤】1 向后撤离1格 无法躲避
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

class DEMO0_API S73 : public Y_CharacterAction//【冲锋】花费15 移动范围3 伤害15 【过载】-1
{
public:
	S73();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S74 : public Y_CharacterAction//【过载攻击】花费15 范围2 伤害15 护盾10 【过载】-2
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

class DEMO0_API S75 : public Y_CharacterAction//【突袭】花费15 移动范围4 伤害10 【过载】-2
{
public:
	S75();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S76 : public Y_CharacterAction//【过载攻击】花费15 范围2 2*（伤害10）【过载】-2
{
public:
	S76();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S77 : public Y_CharacterAction//【脱离】花费15 范围1 伤害10 向后移动2格
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

class DEMO0_API S78 : public Y_CharacterAction//【死战不退】花费20 所有友方+3【过载】
{
public:
	S78();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;
	int32 Hurt;
};

class DEMO0_API S79 : public Y_CharacterAction//【请求支援】花费30 召唤1名禁卫军
{
public:
	S79();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S80 : public Y_CharacterAction//【加固防御】花费20 所有友方+20S
{
public:
	S80();
	virtual float GetWeight()override;

	virtual void ActionChoosed()override;

	virtual void ActionExecute(bool Execute)override;
	int32 DisMT;

};

class DEMO0_API S81 : public Y_CharacterAction//【猛烈攻击】花费20 所有友方+3伤害
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