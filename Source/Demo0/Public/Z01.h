// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Y_Buff.h"
#include "Y_EnemyInfo.h"
#include "Y_CardInfo.h"
#include "Y_RoomWidget.h"
#include "Y_Equipment.h"
#include "Y_Floor.h"

void LZ01();
//私课（50~G，买卡/删卡）
class DEMO0_API E01 :public Y_RoomInfo {
public:
	E01();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//瀑布修炼（-5H，删一，（60%可再次选择（-10H，删一））
class DEMO0_API E02 :public Y_RoomInfo {
public:
	E02();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//福报（-3H，30%得96G，否则再次重复（-6H，50%得96G），否则再次重复（-9H，70%得96G），否则再次重复（诅咒：怨恨，得96G）
class DEMO0_API E03 :public Y_RoomInfo {
public:
	E03();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};
//E3衍生，报官。（去除怨恨）/威胁（得100~G）
class DEMO0_API E04 :public Y_RoomInfo {
public:
	E04();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//欺辱村民。（战斗，得100~G）
class DEMO0_API E05 :public Y_RoomInfo {
public:
	E05();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//战场（找装备，30%进装备，30%进战斗，一直增至100%）
class DEMO0_API E06 :public Y_RoomInfo {
public:
	E06();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//叛徒（100G，获得高稀有度卡）
class DEMO0_API E07 :public Y_RoomInfo {
public:
	E07();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//讲义堂（疑虑，得100~G）
class DEMO0_API E08 :public Y_RoomInfo {
public:
	E08();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//（E8衍生）（去除疑虑，得一张卡）
class DEMO0_API E09 :public Y_RoomInfo {
public:
	E09();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//勾结（50G，无事 / 100~G，战斗）
class DEMO0_API E10 :public Y_RoomInfo {
public:
	E10();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//霸凌（NR）（花50%钱/掉10H）
class DEMO0_API E11 :public Y_RoomInfo {
public:
	E11();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//黄雀在后（战斗/高难战斗，100~G)
class DEMO0_API E12 :public Y_RoomInfo {
public:
	E12();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//见习长老（获得随机卡，获得50~G）
class DEMO0_API E13 :public Y_RoomInfo {
public:
	E13();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//点拨（-20%H，获取等量最大生命值）
class DEMO0_API E14 :public Y_RoomInfo {
public:
	E14();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//试药（随机效果，50~G）
class DEMO0_API E15 :public Y_RoomInfo {
public:
	E15();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//发现卧底（揭发得50~G/威胁得装（30%战斗））
class DEMO0_API E16 :public Y_RoomInfo {
public:
	E16();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//发现卧底（配合（战斗，钱）/揭发（诅咒：羞耻，钱）
class DEMO0_API E17 :public Y_RoomInfo {
public:
	E17();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//老乞丐（-100G）
class DEMO0_API E18 :public Y_RoomInfo {
public:
	E18();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//E4衍生，（装备/卡/高级强化）
class DEMO0_API E19 :public Y_RoomInfo {
public:
	E19();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//参赛守卫（-随机装备，钱）
class DEMO0_API E20 :public Y_RoomInfo {
public:
	E20();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//老铁匠（100G强化，可多次）
class DEMO0_API E21 :public Y_RoomInfo {
public:
	E21();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//试炼（战斗-回20%/删卡）
class DEMO0_API E22 :public Y_RoomInfo {
public:
	E22();
	bool Choosed;
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
	virtual void LeaveRoom()override;
};

//试炼（E8衍生）（难战斗-装备）
class DEMO0_API E23 :public Y_RoomInfo {
public:
	E23();
	bool Choosed;
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
	virtual void LeaveRoom()override;
};

//试炼（E9衍生）（高难战斗-高级强化）
class DEMO0_API E24 :public Y_RoomInfo {
public:
	E24();
	bool Choosed;
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
	virtual void LeaveRoom()override;
};

//野心（50G，加入组织）
class DEMO0_API E25 :public Y_RoomInfo {
public:
	E25();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//E11衍生）（难战斗，装备三选一/背叛，100~G）
class DEMO0_API E26 :public Y_RoomInfo {
public:
	E26();
	bool Choosed;
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
	virtual void LeaveRoom()override;
};

//刺激（NR）（三选一删）
class DEMO0_API E27 :public Y_RoomInfo {
public:
	E27();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//逃亡指挥官（帮助离开（高难战斗）
class DEMO0_API E28 :public Y_RoomInfo {
public:
	E28();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//E2衍生 指挥官的回报（金币/全生二级/高级强化）
class DEMO0_API E29 :public Y_RoomInfo {
public:
	E29();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//隐秘行动（NR）（不作声（40%难战斗）离开（-20%H）
class DEMO0_API E30 :public Y_RoomInfo {
public:
	E30();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//人性（有双方受伤士兵相互扶持）（默不作声，（20%战斗，血量每低2%则加1%概率），120~G / 出手相助，100G，删除所有诅咒卡）
class DEMO0_API E31 :public Y_RoomInfo {
public:
	E31();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//收尸人。（购买二级装备）
class DEMO0_API E32 :public Y_RoomInfo {
public:
	E32();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//专业铁匠。（250高级强化，多次选择）
class DEMO0_API E33 :public Y_RoomInfo {
public:
	E33();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//医院（75G，每次+50G，回20%H/删卡）
class DEMO0_API E34 :public Y_RoomInfo {
public:
	E34();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//装备刷新
class DEMO0_API E35 :public Y_RoomInfo {
public:
	E35();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//功德箱（50G删卡/得200G，诅咒）
class DEMO0_API E36 :public Y_RoomInfo {
public:
	E36();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//云游铁匠（100一次强化或200一次高级强化）
class DEMO0_API E37 :public Y_RoomInfo {
public:
	E37();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//篝火（回30%MaxH / 三选一得卡）
class DEMO0_API E38 :public Y_RoomInfo {
public:
	E38();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//装备商人（100~G一件装备）
class DEMO0_API E39 :public Y_RoomInfo {
public:
	E39();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//对赌（赌自己50%金币，50%翻倍获取）
class DEMO0_API E40 :public Y_RoomInfo {
public:
	E40();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//宝库（100~G / 装备 / 删卡）
class DEMO0_API E41 :public Y_RoomInfo {
public:
	E41();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//陷阱（掉5/掉5Max）
class DEMO0_API E42 :public Y_RoomInfo {
public:
	E42();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//蘑菇（掉15%H回等量Max / 掉10%MaxH回等量H / 50~G）
class DEMO0_API E43 :public Y_RoomInfo {
public:
	E43();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};

//疗养师（50G，回20%/删卡）
class DEMO0_API E44 :public Y_RoomInfo {
public:
	E44();
	virtual TSharedPtr<Y_RoomInfo> RoomClicked()override;
};