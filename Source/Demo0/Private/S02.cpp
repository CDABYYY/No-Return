// Fill out your copyright notice in the Description page of Project Settings.

//#include "S02.h"
#include "S02.h"
#include "Y.h"
#include "Y_GameInstance.h"
#include "Y_Buff.h"
#include "Y_Character.h"
#include "Y_Floor.h"
#include "CameraPawn.h"
#include "Y_StatusBar.h"
#include  "Y_ClassBase.h"
#include "I_Helper.h"
#include "Y_Fighting.h"

using namespace I;

void LS02()
{
	Y::LoadCard<C45>(45);
	Y::LoadCard<C46>(46);
	Y::LoadCard<C47>(47);
	Y::LoadCard<C48>(48);
	Y::LoadCard<C49>(49);
	Y::LoadCard<C50>(50);
	Y::LoadCard<C51>(51);
	Y::LoadCard<C52>(52);
	Y::LoadCard<C53>(53);
	Y::LoadCard<C54>(54);
	Y::LoadCard<C55>(55);
	Y::LoadCard<C56>(56);
	Y::LoadCard<C57>(57);
	Y::LoadCard<C58>(58);
	Y::LoadCard<C59>(59);
	Y::LoadCard<C60>(60);
	Y::LoadCard<C61>(61);
	Y::LoadCard<C62>(62);
	Y::LoadCard<C63>(63);
	Y::LoadCard<C64>(64);
	Y::LoadCard<C65>(65);
	Y::LoadCard<C66>(66);
	Y::LoadCard<C67>(67);
}

BornOFBuff::BornOFBuff() {
	BuffAsType = BuffID = 50;
	TriggerCondition = BeginInjured | AfterInjured;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("浴火"));
}

int32 BornOFBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == BeginInjured) {
		int32 Count = 0;
		auto PA = ToBuffs.FindBuffExtend(3);
		for (auto& p : PA) {
			Count += p->BuffCount;
			p->BuffCount = 0;
		}
		Y_StatusBar S{ Y::YMakeShared<BurnBuff>(Count) };
		ExecuteAction(OwnerCharacter, OwnerCharacter, S);
	}
	else if (ExecuteCondition == AfterInjured) {
		BuffCount -= 1;
		if (BuffCount <= 0)RemoveFromCharacter();
	}
	return 0;
}

C45::C45()
{
	CurrentCost = OriginalCost = 5;
	CardID = 45;
	CardName = Y::PrintText(TEXT("过热思考"));
	BindMessage(TEXT("45"));
	CurrentCardDescribe = Y::PrintText(TEXT("抽5张卡牌, 赋予自己2层【灼烧】"));
}

void C45::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<BurnBuff>(2) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	DrawCard(5, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone18"));
	}
}

bool C45::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C46::C46()
{
	CurrentCost = OriginalCost = 5;
	CardID = 46;
	CardName = Y::PrintText(TEXT("火焰观测"));
	BindMessage(TEXT("46"));
	CurrentCardDescribe = Y::PrintText(TEXT("抽自己【灼烧】层数一半的卡牌"));
}

void C46::Play(bool Execute)
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	DrawCard(buff.Num() > 0 ? buff[0]->BuffCount / 2 : 0, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Body14"));
	}
}

bool C46::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C47::C47()
{
	CurrentCost = OriginalCost = 5;
	CardID = 47;
	CardName = Y::PrintText(TEXT("灼烧伤口"));
	BindMessage(TEXT("47"));
	CurrentCardDescribe = Y::PrintText(TEXT("赋予自己8点【护盾】，2层【灼烧】"));
}

void C47::Play(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(8) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<BurnBuff>(2) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S2, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Body9"));
	}
}

bool C47::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C48::C48()
{
	CurrentCost = OriginalCost = 5;
	CardID = 48;
	CardName = Y::PrintText(TEXT("刺激躯体"));
	BindMessage(TEXT("48"));
	CurrentCardDescribe = Y::PrintText(TEXT("赋予自己3层【灼烧】，清除【虚弱】【易伤】"));
}

void C48::Play(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<BurnBuff>(3) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	auto buff = Y::GetMainCharacter()->Buffs->FindType(6);
	for (auto& p : buff) {
		p->execute(Y::GetMainCharacter(), Y::GetMainCharacter(), *Y::GetMainCharacter()->Buffs, Y_Buff::Ticking, TEXT("IC19"));
		p->RemoveFromCharacter();
	}
	auto buff1 = Y::GetMainCharacter()->Buffs->FindType(7);
	for (auto& p : buff1) {
		p->execute(Y::GetMainCharacter(), Y::GetMainCharacter(), *Y::GetMainCharacter()->Buffs, Y_Buff::Ticking, TEXT("IC19"));
		p->RemoveFromCharacter();
	}
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Body6"));
	}
}

bool C48::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C49::C49()
{
	CurrentCost = OriginalCost = 5;
	CardID = 49;
	CardName = Y::PrintText(TEXT("浴火冲锋"));
	BindMessage(TEXT("49"));
	CurrentCardDescribe = Y::PrintText(TEXT("赋予自己3层【灼烧】，至多冲锋3格，对撞到的敌人施加3层【灼烧】"));
}

void C49::Play(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<BurnBuff>(3) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	if (IsEnemy(Y::GetChoosedFloor()))
	{
		if (ToPos > Pos) ToPos--;
		else ToPos++;
		Move(ToPos - Pos, Execute);
		Y_StatusBar S2{ Y::YMakeShared<BurnBuff>(3) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S2, Execute);
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S1, Execute);
	}
	else
		Move(ToPos - Pos, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName(), Y::GetFloors()[ToPos]);
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone4"));
	}
}

bool C49::AcceptFloor(AY_Floor* GetFloor)
{
	return  CardRange(GetFloor, 3) && !IsBlocked(GetFloor);
}

C50::C50()
{
	CurrentCost = OriginalCost = 5;
	CardID = 50;
	CardName = Y::PrintText(TEXT("火焰护盾"));
	BindMessage(TEXT("50"));
	CurrentCardDescribe = Y::PrintText(TEXT("受到自身【灼烧】层数一半的【伤害】，赋予等同于自己【灼烧】层数的【护盾】"));
}

void C50::Play(bool Execute)
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(buff.Num() > 0 ? buff[0]->BuffCount / 2 : 0) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ShieldBuff>(buff.Num() > 0 ? buff[0]->BuffCount : 0) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S2, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone9"));
	}
}

bool C50::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C51::C51()
{
	CurrentCost = OriginalCost = 5;
	CardID = 51;
	CardName = Y::PrintText(TEXT("浴火"));
	BindMessage(TEXT("51"));
	CurrentCardDescribe = Y::PrintText(TEXT("获得两层【浴火】（将受到的【伤害】转为等层【护盾】）"));
}

void C51::Play(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<BornOFBuff>(2) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone8"));
	}
}

bool C51::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C52::C52()
{
	CurrentCost = OriginalCost = 5;
	CardID = 52;
	CardName = Y::PrintText(TEXT("避火"));
	BindMessage(TEXT("52"));
	CurrentCardDescribe = Y::PrintText(TEXT("获得等同于自身【灼烧】层数的【护盾】"));
}

void C52::Play(bool Execute)
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	Y_StatusBar S{ Y::YMakeShared<ShieldBuff>(buff.Num() > 0 ? buff[0]->BuffCount : 0) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone9"));
	}
}

bool C52::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C53::C53()
{
	CurrentCost = OriginalCost = 5;
	CardID = 53;
	CardName = Y::PrintText(TEXT("火焰爆发"));
	BindMessage(TEXT("53"));
	CurrentCardDescribe = Y::PrintText(TEXT("对附近两格范围内所有敌人造成自身【灼烧】层数的【伤害】"));
}

void C53::Play(bool Execute)
{
	int32 leftBorder, rightBorder;
	int32 tempFloorNum = Y::GetMainCharacter()->StandFloor->SerialNumber;
	Border(tempFloorNum, 2, leftBorder, rightBorder);
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(buff.Num() > 0 ? buff[0]->BuffCount : 0) };
	for (int32 i = leftBorder; i <= rightBorder; i++)
	{
		if (IsValid(Y::GetFloors()[i]) && IsEnemy(Y::GetFloors()[i]))
		{
			ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[i]->StandCharacter, S, Execute);
		}
	}
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone9"));
	}
}

bool C53::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C54::C54()
{
	CurrentCost = OriginalCost = 3;
	CardID = 54;
	CardName = Y::PrintText(TEXT("反思"));
	BindMessage(TEXT("54"));
	CurrentCardDescribe = Y::PrintText(TEXT("弃去手牌并抽取等量的牌"));
}

void C54::Play(bool Execute)
{
	auto TA = Y::GetGameInfo()->InHandCards;
	int32 count = 0;
	for (auto& p : TA)
	{
		Y::GetGameInfo()->UseCard(p, 1);
		count++;
	}
	DrawCard(count, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone15"));
	}
}

bool C54::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C55::C55()
{
	CurrentCost = OriginalCost = 5;
	CardID = 55;
	CardName = Y::PrintText(TEXT("踏火急行"));
	BindMessage(TEXT("55"));
	CurrentCardDescribe = Y::PrintText(TEXT("移动1格，自身每有3层【灼烧】则增加1格移动距离，并对碰到的敌人多造成1层【灼烧】"));
}

void C55::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	if (IsEnemy(Y::GetChoosedFloor()))
	{
		if (ToPos > Pos) ToPos--;
		else ToPos++;
		Move(ToPos - Pos, Execute);
		Y_StatusBar S{ Y::YMakeShared<BurnBuff>(buff.Num() > 0 ? buff[0]->BuffCount / 3 : 0) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	}
	else
		Move(ToPos - Pos, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName(), Y::GetFloors()[ToPos]);
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone2"));
	}
}

bool C55::AcceptFloor(AY_Floor* GetFloor)
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	return CardRange(GetFloor, buff.Num() > 0 ? 1 + buff[0]->BuffCount / 3 : 1) && !IsBlocked(GetFloor);
}

C56::C56()
{
	CurrentCost = OriginalCost = 10;
	CardID = 56;
	CardName = Y::PrintText(TEXT("屏障"));
	BindMessage(TEXT("56"));
	CurrentCardDescribe = Y::PrintText(TEXT("赋予自己15点【护盾】"));
}

void C56::Play(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(15) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone9"));
	}
}

bool C56::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C57::C57()
{
	CurrentCost = OriginalCost = 10;
	CardID = 57;
	CardName = Y::PrintText(TEXT("反击"));
	BindMessage(TEXT("57"));
	CurrentCardDescribe = Y::PrintText(TEXT("如果恢复期间受到攻击则防止其并向选中方向一格反击5点【伤害】"));
}

void C57::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffID = 51;
			BuffName = Y::PrintText(TEXT("反击"));
			TriggerCondition = BeginAction | BeginInjured;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			if (ExecuteCondition == BeginAction)
			{
				BuffCount--;
				if (BuffCount == 0)
					RemoveFromCharacter();
			}
			else if (ExecuteCondition == BeginInjured)
			{
				auto buff = ToBuffs.FindBuffExtend(3);
				if (buff.Num() > 0)
				{
					for (auto& p : buff)
					{
						p->BuffCount = 0;
					}
					int32 pos = OwnerCharacter->StandFloor->SerialNumber + OwnerCharacter->Facing * 1;
					if (IsEnemy(Y::GetFloors()[pos]))
					{
						Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(5) };
						ExecuteAction(OwnerCharacter, Y::GetFloors()[pos]->StandCharacter, S1);
					}
				}
			}
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone9"));
	}
}

bool C57::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C58::C58()
{
	CurrentCost = OriginalCost = 5;
	CardID = 58;
	CardName = Y::PrintText(TEXT("不惜代价"));
	BindMessage(TEXT("58"));
	CurrentCardDescribe = Y::PrintText(TEXT("至多移动3格，对目标和自身造成5点【伤害】"));
}

void C58::Play(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<BurnBuff>(5) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	if (IsEnemy(Y::GetChoosedFloor()))
	{
		if (ToPos > Pos) ToPos--;
		else ToPos++;
		Move(ToPos - Pos, Execute);
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S1, Execute);
	}
	if (Execute)
	{
		PlayMontage(GetMontageName(), Y::GetFloors()[ToPos]);
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone3"));
	}
}

bool C58::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 3) && !IsBlocked(GetFloor) && IsEnemy(GetFloor);
}

C59::C59()
{
	CurrentCost = OriginalCost = 5;
	CardID = 59;
	CardName = Y::PrintText(TEXT("止火"));
	BindMessage(TEXT("59"));
	CurrentCardDescribe = Y::PrintText(TEXT("结算并清除自身【灼烧】"));
}

void C59::Play(bool Execute)
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	for (auto& p : buff) {
		p->execute(Y::GetMainCharacter(), Y::GetMainCharacter(), *Y::GetMainCharacter()->Buffs, Y_Buff::Ticking, TEXT("C59"), Execute);
		p->RemoveFromCharacter();
	}
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone20"));
	}
}

bool C59::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C60::C60()
{
	CurrentCost = OriginalCost = 10;
	CardID = 60;
	CardName = Y::PrintText(TEXT("烈火予身"));
	BindMessage(TEXT("60"));
	CurrentCardDescribe = Y::PrintText(TEXT("在【灼烧】结算前向附近1格的敌人施加自身【灼烧】层数一半的【灼烧】"));
}

void C60::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffName = Y::PrintText(TEXT("烈火矛身"));
			BuffOrder = -10;
			TriggerCondition = Ticking;
			BuffID = 1060;
			BuffCount = 1;
		}
		virtual int32 execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)override {
			auto Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
			if (Pos + 1 <= Y::GetFloors().Num()) {
				auto F = Y::GetFloors()[Pos + 1];
				if (IsValid(F) && IsEnemy(F)) {
					auto A = Y::GetMainCharacter()->Buffs->FindType(5);
					if (A.Num() > 0)
					{
						Y_StatusBar BS{ Y::YMakeShared<BurnBuff>(A[0]->BuffCount / 2) };
						Y::ExecuteAction(Y::GetMainCharacter(), F->StandCharacter, BS, TEXT(""), TryAttack);
					}
				}
			}
			if (Pos - 1 >= 0) {
				auto F = Y::GetFloors()[Pos - 1];
				if (IsValid(F) && IsEnemy(F)) {
					auto A = Y::GetMainCharacter()->Buffs->FindType(5);
					if (A.Num() > 0)
					{
						Y_StatusBar BS{ Y::YMakeShared<BurnBuff>(A[0]->BuffCount / 2) };
						Y::ExecuteAction(Y::GetMainCharacter(), F->StandCharacter, BS, TEXT(""), TryAttack);
					}
				}
			}
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone19"));
	}
}

bool C60::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C61::C61()
{
	CurrentCost = OriginalCost = 10;
	CardID = 61;
	CardName = Y::PrintText(TEXT("火焰研习"));
	BindMessage(TEXT("61"));
	CurrentCardDescribe = Y::PrintText(TEXT("每受到3点【灼烧】抽1张卡牌"));
}

void C61::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffID = 52;
			BuffName = Y::PrintText(TEXT("火焰研习"));
			TriggerCondition = BeginTick;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto buff = OwnerCharacter->Buffs->FindType(5);
			int32 Count = buff[0]->BuffCount / 3;
			Y::GetGameInfo()->DrawCard(Count);
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone21"));
	}
}

bool C61::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C62::C62()
{
	CurrentCost = OriginalCost = 10;
	CardID = 62;
	CardName = Y::PrintText(TEXT("火焰熟练"));
	BindMessage(TEXT("62"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成【灼烧】时附加自身【灼烧】层数的1/5"));
}

void C62::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffID = 53;
			BuffName = Y::PrintText(TEXT("火焰熟练"));
			TriggerCondition = BeginBuff;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto buff = OwnerCharacter->Buffs->FindType(5);
			int32 Count = buff[0]->BuffCount / 5;
			Y_StatusBar S1{ Y::YMakeShared<BurnBuff>(Count) };
			ExecuteAction(OwnerCharacter, OwnerCharacter, S1);
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone18"));
	}
}

bool C62::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C63::C63()
{
	CurrentCost = OriginalCost = 10;
	CardID = 63;
	CardName = Y::PrintText(TEXT("火焰精通"));
	BindMessage(TEXT("63"));
	CurrentCardDescribe = Y::PrintText(TEXT("在受到灼烧伤害前获得自身【灼烧】层数一半的【护盾】"));
}

void C63::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffID = 54;
			BuffName = Y::PrintText(TEXT("火焰精通"));;
			TriggerCondition = BeginInjured;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto buff = OwnerCharacter->Buffs->FindType(32);
			if (buff[0]->BuffCount > 0)
			{
				int32 Count = buff[0]->BuffCount / 2;
				Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(Count) };
				ExecuteAction(OwnerCharacter, OwnerCharacter, S1);
			}
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone9"));
	}
}

bool C63::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C64::C64()
{
	CurrentCost = OriginalCost = 10;
	CardID = 64;
	CardName = Y::PrintText(TEXT("火焰掌控"));
	BindMessage(TEXT("64"));
	CurrentCardDescribe = Y::PrintText(TEXT("当自身【灼烧】层数大于8时，普通攻击将附加1层【灼烧】"));
}

void C64::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffID = 55;
			BuffName = Y::PrintText(TEXT("火焰掌控"));
			TriggerCondition = BeginAttack;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto buff = OwnerCharacter->Buffs->FindType(5);
			if (buff[0]->BuffCount > 8)
			{
				auto buff1 = ToBuffs.FindBuffExtend(3);
				if (buff1.Num() > 0)
				{
					Y_StatusBar S1{ Y::YMakeShared<BurnBuff>(1) };
					ExecuteAction(OwnerCharacter, ToCharacter, S1);
				}
			}
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone13"));
	}
}

bool C64::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C65::C65()
{
	CurrentCost = OriginalCost = 10;
	CardID = 65;
	CardName = Y::PrintText(TEXT("火势蔓延"));
	BindMessage(TEXT("65"));
	CurrentCardDescribe = Y::PrintText(TEXT("当自身【灼烧】层数大于10时，每次自身获得【灼烧】后触发【烈火予身】效果"));
}

void C65::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffID = 56;
			BuffName = Y::PrintText(TEXT("火势蔓延"));
			TriggerCondition = BeginBuffed;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto buff = ToBuffs.FindType(6);
			auto p = OwnerCharacter->Buffs->FindType(5);
			if (buff.Num() > 0 && p[0]->BuffCount > 10)
			{
				int32 left, right;
				Border(OwnerCharacter->StandFloor->SerialNumber, 1, left, right);
				TArray<int32> AccPos;
				for (int32 i = left; i <= right; i++)
				{
					if (IsEnemy(Y::GetFloors()[i]))
					{
						AccPos.Add(i);
					}
				}
				if (AccPos.Num() > 0)
				{
					int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
					int32 Count = (p[0]->BuffCount + buff[0]->BuffCount) / 2;
					Y_StatusBar S1{ Y::YMakeShared<BurnBuff>(Count) };
					ExecuteAction(OwnerCharacter, Y::GetFloors()[EnemyPos]->StandCharacter, S1);
				}
			}
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone12"));
	}
}

bool C65::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C66::C66()
{
	CurrentCost = OriginalCost = 10;
	CardID = 66;
	CardName = Y::PrintText(TEXT("火势扩张"));
	BindMessage(TEXT("66"));
	CurrentCardDescribe = Y::PrintText(TEXT("当自身【灼烧】层数大于10时，每次攻击后全场获得1层【灼烧】"));
}

void C66::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffID = 57;
			BuffName = Y::PrintText(TEXT("火势扩张"));
			TriggerCondition = BeginAttack;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto buff = OwnerCharacter->Buffs->FindType(5);
			if (buff.Num() > 0 && buff[0]->BuffCount > 10)
			{
				auto buff1 = ToBuffs.FindBuffExtend(3);
				if (buff1.Num() > 0)
				{
					for (auto& p : Y::GetEnemys())
					{
						Y_StatusBar S1{ Y::YMakeShared<BurnBuff>(1) };
						ExecuteAction(OwnerCharacter, p, S1);
					}
				}
			}
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone7"));
	}
}

bool C66::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

C67::C67()
{
	CurrentCost = OriginalCost = 5;
	CardID = 67;
	CardName = Y::PrintText(TEXT("搜索预案"));
	BindMessage(TEXT("67"));
	CurrentCardDescribe = Y::PrintText(TEXT("抽卡至六张"));
}

void C67::Play(bool Execute)
{
	int32 Count = Y::GetGameInfo()->InHandCards.Num();
	if (Count < 6)
	{
		DrawCard(6 - Count, Execute);
	}
	if (Execute)
	{
		PlayMontage(GetMontageName());
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone8"));
	}
}

bool C67::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

