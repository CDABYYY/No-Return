// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Y_CardInfo.h"

void L_I01();

//C1（N）【延山式：掌】4T，5D，1R
class DEMO0_API C01 :public Y_CardInfo
{
public:
	C01();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C2（N）【延山步】10T，2M
class DEMO0_API C02 :public Y_CardInfo
{
public:
	C02();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C3（N）【延山式：拳】5T，5D，1R，如果有【虚弱】+5D
class DEMO0_API C03 :public Y_CardInfo
{
public:
	C03();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C4（N）【冲锋】5T，对某个方向最多移动两格，遇到敌人则停止并造成5D
class DEMO0_API C04 :public Y_CardInfo
{
public:
	C04();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C5（N）【延山式：扫荡】4T，1R，4D，前后一格都造成伤害。
class DEMO0_API C05 :public Y_CardInfo
{
public:
	C05();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C6（N）【延山式：痛击】5T，1R，4D，每造成2点伤害抽一张牌
class DEMO0_API C06 :public Y_CardInfo
{
public:
	C06();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C7（N）【延山式：撼地】5T，对前方两格敌人造成4D，1层【易伤】
class DEMO0_API C07 :public Y_CardInfo
{
public:
	C07();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C8（R）【最终手段】3T，当手牌中没有【延山式】时，10D,1R，3C
class DEMO0_API C08 :public Y_CardInfo
{
public:
	C08();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C9（R）【调整脚步】5T，1M
class DEMO0_API C09 :public Y_CardInfo
{
public:
	C09();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C10（R）【一击脱离】4T，4D，1R，向后位移至多2格
class DEMO0_API C10 :public Y_CardInfo
{
public:
	C10();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C11（R）【延山式：冲拳】6T，2R，同【冲锋】，每次使用-1T
class DEMO0_API C11 :public Y_CardInfo
{
public:
	C11();
	virtual void BeginFighting()override;
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C12（R）【延山式：绵掌】4T，1R，4D，将一张【延山式：绵掌】置入弃牌堆
class DEMO0_API C12 :public Y_CardInfo
{
public:
	C12();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C13（R）【延山式：迅击】8T，1R，2D*3，每次使用+1次伤害
class DEMO0_API C13 :public Y_CardInfo
{
public:
	C13();
	int32 num;
	virtual void BeginFighting()override;
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C14（R）（P）【迅捷架势】8T，减少所有【延山式】1点消耗
class DEMO0_API C14 :public Y_CardInfo
{
public:
	C14();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C15（R）（P）【重击架势】8T，增加所有【延山式】1点伤害
class DEMO0_API C15 :public Y_CardInfo
{
public:
	C15();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C16（R）（P）【连绵架势】8T，每打出两张【延山式】，抽一张卡
class DEMO0_API C16 :public Y_CardInfo
{
public:
	C16();
	int32 num;
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C17（R）【延山式：研习】5T，5D，1R，该卡每次造成击杀则+2伤害
class DEMO0_API C17 :public Y_CardInfo
{
public:
	C17();
	int32 Kill;
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C18（R）【奋力一搏】4T，3R，5D，同【冲锋】，在抽牌堆中增加一【晕眩】（2T，无效果）
class DEMO0_API C18 :public Y_CardInfo
{
public:
	C18();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C19（R）【延山式：透劲】5T，5D，2R，对前方2格所有敌人造成伤害
class DEMO0_API C19 :public Y_CardInfo
{
public:
	C19();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C20（SR）（E）【延山式：乱击】4T，5D，1R，在手牌上获得一张+1伤害的【延山式：乱击】，新的卡牌将在打出一张其他卡牌前消耗
class DEMO0_API C20 :public Y_CardInfo
{
public:
	C20();
	int32 extra;
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C21（R）【延山式：断骨】6T，1R，4D，2层【易伤】（增伤普攻25%）
class DEMO0_API C21 :public Y_CardInfo
{
public:
	C21();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C22（R）【延山式：摧筋】6T，1R，4D，2层【虚弱】（降低伤害25%）
class DEMO0_API C22 :public Y_CardInfo
{
public:
	C22();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C23（SR）【延山式：诸武精通】10T，10D，对一个方向三格内所有敌人造成伤害，手牌，抽牌堆，弃牌堆每有一张【延山式】则增加2点伤害。
class DEMO0_API C23 :public Y_CardInfo
{
public:
	C23();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C24（SR）（E）【延山式：爆发】10T，向一个方向打出手牌中所有【延山式】
class DEMO0_API C24 :public Y_CardInfo
{
public:
	C24();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C25（N）【防御】5T，-6S
class DEMO0_API C25 :public Y_CardInfo
{
public:
	C25();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C26（N）【过载思考】3T，-2B，4C
class DEMO0_API C26 :public Y_CardInfo
{
public:
	C26();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C27（N）【点火】4T，2R，3B
class DEMO0_API C27 :public Y_CardInfo
{
public:
	C27();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C28（N）【烈焰击】4T，1R，3D，附加目标B/3 的D
class DEMO0_API C28 :public Y_CardInfo
{
public:
	C28();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C29（N）【火焰释放】8T，3R，对目标方向最远3格所有敌人施加6B
class DEMO0_API C29 :public Y_CardInfo
{
public:
	C29();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C30（P）（R）【掌握火势】10T，施加B将额外施加1层
class DEMO0_API C30 :public Y_CardInfo
{
public:
	C30();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C31（E）（R）【渐热】5T，2B，每次使用＋1B
class DEMO0_API C31 :public Y_CardInfo
{
public:
	C31();
	int32 num;
	virtual void BeginFighting()override;
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C32（R）【煽风点火】8T，2R，2B＊3
class DEMO0_API C32 :public Y_CardInfo
{
public:
	C32();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C33（R）【助长火势】5T，2R，4B，如果目标有10B则4C
class DEMO0_API C33 :public Y_CardInfo
{
public:
	C33();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C34（N）【趁火打劫】5T，4D，如果目标有B则再次4D
class DEMO0_API C34 :public Y_CardInfo
{
public:
	C34();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C35（R）【引火】8T，3R，对目标施加2层【着火】（每次被施加B额外造成1B）
class DEMO0_API C35 :public Y_CardInfo
{
public:
	C35();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C36（R）【燃烧】8T，3R，对目标施加2层【猛燃】（被燃烧造成双倍伤害）
class DEMO0_API C36 :public Y_CardInfo
{
public:
	C36();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C37（R）【火焰连打】8T，（2D1B）*4
class DEMO0_API C37 :public Y_CardInfo
{
public:
	C37();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C38（R）【助燃】6T，3R，目标B每有2层施加1B
class DEMO0_API C38 :public Y_CardInfo
{
public:
	C38();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C39（R）【嗜火】5T，1M，目标B每有3层增加一移动距离
class DEMO0_API C39 :public Y_CardInfo
{
public:
	C39();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C40（R）【以火作衣】6T，3R，获得等同于目标B层数的护盾
class DEMO0_API C40 :public Y_CardInfo
{
public:
	C40();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C41（R）【引燃】8T，2R2A，对范围内所有单位施加6B
class DEMO0_API C41 :public Y_CardInfo
{
public:
	C41();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C42（P）（SR）【不息烈火】10T，所有人的灼烧层数不再降低
class DEMO0_API C42 :public Y_CardInfo
{
public:
	C42();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C43（R）【引燃】8T，结算目标B
class DEMO0_API C43 :public Y_CardInfo
{
public:
	C43();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C44（SR）【死亡莲华】15T，对所有敌方目标使用【引燃】，如果有敌方目标在此过程中死亡则再次使用【死亡莲华】
class DEMO0_API C44 :public Y_CardInfo
{
public:
	C44();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C2001【疑虑】无效果，3T打出
class DEMO0_API C2001 :public Y_CardInfo
{
public:
	C2001();
	virtual FText LogDescript()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C2002【痛苦】-3D，在手牌中每张卡-1D
class DEMO0_API C2002 :public Y_CardInfo
{
public:
	C2002();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
	virtual void Drawed()override;
	virtual void Leave()override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C2003【愤怒】3T，3D，1R，再次塞入【愤怒】
class DEMO0_API C2003 :public Y_CardInfo
{
public:
	C2003();
	virtual FText LogDescript()override;
	virtual void Play(bool Execute)override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C2004【晕眩】无效果，无法打出
class DEMO0_API C2004 :public Y_CardInfo
{
public:
	C2004();
	virtual FText LogDescript()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};

//C2005【羞耻】5T打出，在手牌中每张卡+1T
class DEMO0_API C2005 :public Y_CardInfo
{
public:
	C2005();
	virtual FText LogDescript()override;
	virtual bool AcceptFloor(class AY_Floor* GetFloor)override;
	virtual void Drawed()override;
	virtual void Leave()override;

	/*	virtual FText GetCardDescribe()override;
		virtual FText GetPointDescribe()override;*/
};
