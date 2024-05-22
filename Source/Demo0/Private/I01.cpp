// Fill out your copyright notice in the Description page of Project Settings.


#include "I01.h"
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
#include "A01.h"

using namespace I;

void L_I01()
{
	Y::LoadCard<C01>(1);
	Y::LoadCard<C02>(2);
	Y::LoadCard<C03>(3);
	Y::LoadCard<C04>(4);
	Y::LoadCard<C05>(5);
	Y::LoadCard<C06>(6);
	Y::LoadCard<C07>(7);
	Y::LoadCard<C08>(8);
	Y::LoadCard<C09>(9);
	Y::LoadCard<C10>(10);
	Y::LoadCard<C11>(11);
	Y::LoadCard<C12>(12);
	Y::LoadCard<C13>(13);
	Y::LoadCard<C14>(14);
	Y::LoadCard<C15>(15);
	Y::LoadCard<C16>(16);
	Y::LoadCard<C17>(17);
	Y::LoadCard<C18>(18);
	Y::LoadCard<C19>(19);
	Y::LoadCard<C20>(20);
	Y::LoadCard<C21>(21);
	Y::LoadCard<C22>(22);
	Y::LoadCard<C23>(23);
	Y::LoadCard<C24>(24);
	Y::LoadCard<C25>(25);
	Y::LoadCard<C26>(26);
	Y::LoadCard<C27>(27);
	Y::LoadCard<C28>(28);
	Y::LoadCard<C29>(29);
	Y::LoadCard<C30>(30);
	Y::LoadCard<C31>(31);
	Y::LoadCard<C32>(32);
	Y::LoadCard<C33>(33);
	Y::LoadCard<C34>(34);
	Y::LoadCard<C35>(35);
	Y::LoadCard<C36>(36);
	Y::LoadCard<C37>(37);
	Y::LoadCard<C38>(38);
	Y::LoadCard<C39>(39);
	Y::LoadCard<C40>(40);
	Y::LoadCard<C41>(41);
	Y::LoadCard<C42>(42);
	Y::LoadCard<C43>(43);
	Y::LoadCard<C44>(44);
	Y::LoadCard<C2001>(2001);
	Y::LoadCard<C2002>(2002);
	Y::LoadCard<C2003>(2003);
	Y::LoadCard<C2004>(2004);
	Y::LoadCard<C2005>(2005);
}

/*------------------------------------C01--------------------------------------*/

C01::C01()
{
	CurrentCost = OriginalCost = 4;
	CardID = 1;
	CardTypes.Add(1);
	CardRare = 1;
	CardName = Y::PrintText(TEXT("延山式：掌"));
	BindMessage(TEXT("1"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成5点伤害"));
}

FText C01::LogDescript()
{
	return FText();
}

void C01::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone1"));
		PlayMontage(GetMontageName());
	}
}

bool C01::AcceptFloor(AY_Floor* GetFloor)
{
	return  CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C01--------------------------------------*/
/*------------------------------------C02--------------------------------------*/

C02::C02()
{
	CurrentCost = OriginalCost = 10;
	CardID = 2;
	CardRare = 1;
	CardName = Y::PrintText(TEXT("延山步"));
	BindMessage(TEXT("2"));
	CurrentCardDescribe = Y::PrintText(TEXT("移动2格"));
}

FText C02::LogDescript()
{
	return FText();
}

void C02::Play(bool Execute)
{
	int32 moveInstance = Y::GetChoosedFloor()->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	Move(moveInstance, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone13"));
		PlayMontage(GetMontageName(), Y::GetChoosedFloor());
	}
}

bool C02::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && !IsBlocked(GetFloor) && !IsEnemy(GetFloor);
}

/*------------------------------------C02--------------------------------------*/
/*------------------------------------C03--------------------------------------*/

C03::C03()
{
	CurrentCost = OriginalCost = 5;
	CardID = 3;
	CardTypes.Add(1);
	CardRare = 1;
	CardName = Y::PrintText(TEXT("延山式：拳"));
	BindMessage(TEXT("3"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成5点伤害，如果敌人虚弱则改为10点"));
}

FText C03::LogDescript()
{
	return FText();
}

void C03::Play(bool Execute)
{
	int32 extra = 0;
	auto buff = Y::GetChoosedFloor()->StandCharacter->Buffs->FindType(6);
	if (buff.Num() > 0)extra = 5;
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5 + extra) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone3"));
		PlayMontage(GetMontageName());
	}
}

bool C03::AcceptFloor(AY_Floor* GetFloor)
{
	return  CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C03--------------------------------------*/
/*------------------------------------C04--------------------------------------*/

C04::C04()
{
	CurrentCost = OriginalCost = 5;
	CardID = 4;
	CardRare = 1;
	CardName = Y::PrintText(TEXT("冲锋"));
	BindMessage(TEXT("4"));
	CurrentCardDescribe = Y::PrintText(TEXT("最多移动2格，遇到敌人停止并对其造成5点伤害"));
}

FText C04::LogDescript()
{
	return FText();
}

void C04::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	if (IsEnemy(Y::GetChoosedFloor()))
	{
		if (ToPos > Pos) ToPos--;
		else ToPos++;
		Move(ToPos - Pos, Execute);
		Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	}
	else
		Move(ToPos - Pos, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone4"));
		PlayMontage(GetMontageName(), Y::GetFloors()[ToPos]);
	}
}

bool C04::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && !IsBlocked(GetFloor);
}

/*------------------------------------C04--------------------------------------*/
/*------------------------------------C05--------------------------------------*/

C05::C05()
{
	CurrentCost = OriginalCost = 4;
	CardID = 5;
	CardTypes.Add(1);
	CardRare = 1;
	CardName = Y::PrintText(TEXT("延山式：扫荡"));
	BindMessage(TEXT("5"));
	CurrentCardDescribe = Y::PrintText(TEXT("前后1格内的敌人各造成4点伤害"));
}

FText C05::LogDescript()
{
	return FText();
}

void C05::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	if (IsEnemy(Y::GetFloors()[Pos - 1]))
	{
		Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[Pos - 1]->StandCharacter, S, Execute);
	}
	if (IsEnemy(Y::GetFloors()[Pos + 1]))
	{
		Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[Pos + 1]->StandCharacter, S, Execute);
	}
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone8"));
		PlayMontage(GetMontageName());
	}
}

bool C05::AcceptFloor(AY_Floor* GetFloor)
{
	return  CardRange(GetFloor, 1);
}

/*------------------------------------C05--------------------------------------*/
/*------------------------------------C06--------------------------------------*/

C06::C06()
{
	CurrentCost = OriginalCost = 5;
	CardID = 6;
	CardTypes.Add(1);
	CardRare = 1;
	CardName = Y::PrintText(TEXT("延山式：扫荡"));
	BindMessage(TEXT("6"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成4点伤害，每造成4点伤害抽一张卡"));
}

FText C06::LogDescript()
{
	return FText();
}

void C06::Play(bool Execute)
{
	auto P = Y::YMakeShared<DemageBuff>(4);
	Y_StatusBar S{ P };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	int32 Demage = P->BuffCount;
	DrawCard(Demage / 2, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone12"));
		PlayMontage(GetMontageName());
	}
}

bool C06::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C06--------------------------------------*/
/*------------------------------------C07--------------------------------------*/

C07::C07()
{
	CurrentCost = OriginalCost = 5;
	CardID = 7;
	CardTypes.Add(1);
	CardRare = 1;
	CardName = Y::PrintText(TEXT("延山式：撼地"));
	BindMessage(TEXT("7"));
	CurrentCardDescribe = Y::PrintText(TEXT("对前方2格敌人造成4点伤害，并施加一层易伤"));
}

FText C07::LogDescript()
{
	return FText();
}

void C07::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	int32 leftBorder, rightBorder;
	Border(Pos, 2, leftBorder, rightBorder, ToPos > Pos);
	for (int32 i = leftBorder; i <= rightBorder; i++)
	{
		if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter))
		{
			Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(4) };
			ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[i]->StandCharacter, S1, Execute);
			Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(1) };
			ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[i]->StandCharacter, S2, Execute);
		}
	}
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone6"));
		PlayMontage(GetMontageName());
	}
}

bool C07::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && GetFloor != Y::GetMainCharacter()->StandFloor;
}

/*------------------------------------C07--------------------------------------*/
/*------------------------------------C08--------------------------------------*/

C08::C08()
{
	CurrentCost = OriginalCost = 3;
	CardID = 8;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("最终手段"));
	BindMessage(TEXT("8"));
	CurrentCardDescribe = Y::PrintText(TEXT("当手中没有延山式时可以打出，造成10点伤害，抽3张卡"));
}

FText C08::LogDescript()
{
	return FText();
}

void C08::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(10) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	DrawCard(3, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone5"));
		PlayMontage(GetMontageName());
	}
}

bool C08::AcceptFloor(AY_Floor* GetFloor)
{
	for (auto& p : Y::GetGameInfo()->InHandCards) {
		if (p->CardTypes.Contains(1)) {
			return false;
		}
	}
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C08--------------------------------------*/
/*------------------------------------C09--------------------------------------*/

C09::C09()
{
	CurrentCost = OriginalCost = 5;
	CardID = 9;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("调整脚步"));
	BindMessage(TEXT("9"));
	CurrentCardDescribe = Y::PrintText(TEXT("移动1格"));
}

FText C09::LogDescript()
{
	return FText();
}

void C09::Play(bool Execute)
{
	Move(1, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone13"));
		PlayMontage(GetMontageName(), Y::GetChoosedFloor());
	}
}

bool C09::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && !IsEnemy(GetFloor);
}

/*------------------------------------C09--------------------------------------*/
/*------------------------------------C10--------------------------------------*/

C10::C10()
{
	CurrentCost = OriginalCost = 4;
	CardID = 10;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("一击脱离"));
	BindMessage(TEXT("10"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成4点伤害，后撤至多2格"));
}

FText C10::LogDescript()
{
	return FText();
}

void C10::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(4) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ChPos = Y::GetChoosedFloor()->SerialNumber;
	int32 ToPos = End(Pos, 2, ChPos < Pos);
	Move(ToPos - Pos, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone13"));
		PlayMontage(GetMontageName(), Y::GetFloors()[ToPos]);
	}
}

bool C10::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C10--------------------------------------*/
/*------------------------------------C11--------------------------------------*/

C11::C11()
{
	CurrentCost = OriginalCost = 6;
	CardID = 11;
	CardTypes.Add(1);
	CardRare = 2;
	CardName = Y::PrintText(TEXT("延山式：冲拳"));
	BindMessage(TEXT("11"));
	CurrentCardDescribe = Y::PrintText(TEXT("冲刺2格，每使用一次减少1耗费"));
}

void C11::BeginFighting()
{
	OriginalCost = 6;
}

FText C11::LogDescript()
{
	return FText();
}

void C11::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	if (IsEnemy(Y::GetChoosedFloor()))
	{
		if (ToPos > Pos) ToPos--;
		else ToPos++;
		Move(ToPos - Pos, Execute);
		Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	}
	else
		Move(ToPos - Pos, Execute);
	OriginalCost--;
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone4"));
		PlayMontage(GetMontageName(), Y::GetFloors()[ToPos]);
	}
}

bool C11::AcceptFloor(AY_Floor* GetFloor)
{
	return  CardRange(GetFloor, 2) && !IsBlocked(GetFloor);
}

/*------------------------------------C11--------------------------------------*/
/*------------------------------------C12--------------------------------------*/

C12::C12()
{
	CurrentCost = OriginalCost = 4;
	CardID = 12;
	CardTypes.Add(1);
	CardRare = 2;
	CardName = Y::PrintText(TEXT("延山式：绵掌"));
	BindMessage(TEXT("12"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成4点伤害，将一张延山式：绵拳加入弃牌堆"));
}

FText C12::LogDescript()
{
	return FText();
}

void C12::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(4) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	Y::GetGameInfo()->ExhaustCards.Add(MakeShared<C12>());
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone12"));
		PlayMontage(GetMontageName());
	}
}

bool C12::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C12--------------------------------------*/
/*------------------------------------C13--------------------------------------*/

C13::C13()
{
	CurrentCost = OriginalCost = 8;
	CardID = 13;
	CardTypes.Add(1);
	CardRare = 2;
	CardName = Y::PrintText(TEXT("延山式：迅击"));
	BindMessage(TEXT("13"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成2点伤害3次，每次使用伤害+1"));
	num = 0;
}

void C13::BeginFighting()
{
	num = 0;
}

FText C13::LogDescript()
{
	return FText();
}

void C13::Play(bool Execute)
{
	for (int32 i = 0; i < 3; i++)
	{
		Y_StatusBar S{ Y::YMakeShared<DemageBuff>(2 + num) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	}
	num++;
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone2"));
		PlayMontage(GetMontageName());
	}
}

bool C13::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C13--------------------------------------*/
/*------------------------------------C14--------------------------------------*/

C14::C14()
{
	CurrentCost = OriginalCost = 8;
	CardID = 14;
	UsedType = 3;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("迅捷架势"));
	BindMessage(TEXT("14"));
	CurrentCardDescribe = Y::PrintText(TEXT("减少所有延山式1点消耗"));
}

FText C14::LogDescript()
{
	return FText();
}

void C14::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() {
			TriggerCondition = BeginAction;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto& p = ToBuffs.Buff[0];
			/*p->BuffExtend = PC->CardTypes;
			p->BuffCount = PC->CurrentCost;
			p->BuffID = 10000 + PC->CardID;*/
			if (p->BuffExtend.Contains(1)) {
				p->BuffCount--;
			}
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), GetOwner(), S, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone10"));
		PlayMontage(GetMontageName());
	}
}

bool C14::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

/*------------------------------------C14--------------------------------------*/
/*------------------------------------C15--------------------------------------*/

C15::C15()
{
	CurrentCost = OriginalCost = 8;
	CardID = 15;
	UsedType = 3;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("重击架势"));
	BindMessage(TEXT("15"));
	CurrentCardDescribe = Y::PrintText(TEXT("增加所有延山式1点伤害"));
}

FText C15::LogDescript()
{
	return FText();
}

void C15::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() { BuffCount = 1; BuffID = 1015; TriggerCondition = BeginAttack; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto& p = ToBuffs.Buff[0];
			if (p->BuffExtend.Contains(1)) {
				auto TA = ToBuffs.FindBuffExtend(3);
				for (auto& p0 : TA)p0->BuffCount += BuffCount;
			}
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), GetOwner(), S, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone7"));
		PlayMontage(GetMontageName());
	}
}

bool C15::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

/*------------------------------------C15--------------------------------------*/
/*------------------------------------C16--------------------------------------*/

C16::C16()
{
	CurrentCost = OriginalCost = 8;
	CardID = 16;
	UsedType = 3;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("连绵架势"));
	BindMessage(TEXT("16"));
	CurrentCardDescribe = Y::PrintText(TEXT("每打出2张延山式抽1张卡"));
	num = 0;
}

FText C16::LogDescript()
{
	return FText();
}

void C16::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		C16* PC;
		TB(C16* P) {
			TriggerCondition = BeginAction;
			PC = P;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto& p = ToBuffs.Buff[0];
			/*
			p->BuffExtend = PC->CardTypes;
			p->BuffCount = PC->CurrentCost;
			p->BuffID = 10000 + PC->CardID;*/
			if (p->BuffExtend.Contains(1)) {
				PC->num++;
			}
			if (PC->num == 2)
			{
				Y::GetGameInfo()->DrawCard();
				PC->num = 0;
			}
			return 0;
		}
	};
	auto TP = MakeShared<TB>(this);
	Y_StatusBar S{ TP };
	DrawCard(1, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone10"));
		PlayMontage(GetMontageName());
	}
}

bool C16::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

/*------------------------------------C16--------------------------------------*/
/*------------------------------------C17--------------------------------------*/

C17::C17()
{
	CurrentCost = OriginalCost = 5;
	CardID = 17;
	CardTypes.Add(1);
	CardRare = 2;
	CardName = Y::PrintText(TEXT("延山式：研习"));
	BindMessage(TEXT("17"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成5点伤害，每次击杀伤害加2"));
	Kill = 0;
}

FText C17::LogDescript()
{
	return FText();
}

void C17::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		C17* PC;
		TB(C17* P) {
			TriggerCondition = AfterKill;
			PC = P;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			PC->Kill++;
			return 0;
		}
	};
	auto TP = MakeShared<TB>(this);
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5 + Kill * 2) ,TP };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone2"));
		PlayMontage(GetMontageName());
	}
}

bool C17::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C17--------------------------------------*/
/*------------------------------------C18--------------------------------------*/

C18::C18()
{
	CurrentCost = OriginalCost = 4;
	CardID = 18;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("奋力一搏"));
	BindMessage(TEXT("18"));
	CurrentCardDescribe = Y::PrintText(TEXT("冲刺3格，造成5点伤害，在抽牌堆中增加一张【眩晕】"));
}

FText C18::LogDescript()
{
	return FText();
}

void C18::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	if (IsEnemy(Y::GetChoosedFloor()))
	{
		if (ToPos > Pos) ToPos--;
		else ToPos++;
		Move(ToPos - Pos, Execute);
		Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	}
	else
		Move(ToPos - Pos, Execute);
	Y::GetGameInfo()->ToDrawCards.Add(MakeShared<C2004>());
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone6"));
		PlayMontage(GetMontageName(), Y::GetFloors()[ToPos]);
	}
}

bool C18::AcceptFloor(AY_Floor* GetFloor)
{
	return  CardRange(GetFloor, 3) && !IsBlocked(GetFloor);
}

/*------------------------------------C18--------------------------------------*/
/*------------------------------------C19--------------------------------------*/

C19::C19()
{
	CurrentCost = OriginalCost = 5;
	CardID = 19;
	CardTypes.Add(1);
	CardRare = 2;
	CardName = Y::PrintText(TEXT("延山式：透劲"));
	BindMessage(TEXT("19"));
	CurrentCardDescribe = Y::PrintText(TEXT("对前方2格敌人造成5点伤害"));
}

FText C19::LogDescript()
{
	return FText();
}

void C19::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	int32 leftBorder, rightBorder;
	Border(Pos, 2, leftBorder, rightBorder, ToPos > Pos);
	for (int32 i = leftBorder; i <= rightBorder; i++)
	{
		if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter))
		{
			Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5) };
			ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[i]->StandCharacter, S, Execute);
		}
	}
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone5"));
		PlayMontage(GetMontageName());
	}
}

bool C19::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && GetFloor != Y::GetMainCharacter()->StandFloor;
}

/*------------------------------------C19--------------------------------------*/
/*------------------------------------C20--------------------------------------*/

C20::C20()
{
	CurrentCost = OriginalCost = 4;
	CardID = 20;
	CardTypes.Add(1);
	UsedType = 1;
	CardRare = 3;
	CardName = Y::PrintText(TEXT("奋力一搏"));
	BindMessage(TEXT("20"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成5点伤害，获得1张持续1回合的【延山式：乱击】"));
	extra = 0;
}

FText C20::LogDescript()
{
	return FText();
}

void C20::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TSharedPtr<Y_CardInfo> Card;
		C20* GetThis;
		TB(TSharedPtr<Y_CardInfo> PC, C20* Get) {
			GetThis = Get;
			Card = PC;
			TriggerCondition = BeginAction;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto& p = ToBuffs.Buff[0];
			if (p->BuffID != 10000 + Card->CardID) {
				GetThis->extra = 0;
				Y::GetGameInfo()->UseCard(Card, 1);
				RemoveFromCharacter();
			}
			return 0;
		}
	};
	auto TP = MakeShared<TB>(SharedThis(this), this);
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5 + extra),TP };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	Y::GetGameInfo()->InHandCards.Add(SharedThis(this));
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone4"));
		PlayMontage(GetMontageName());
	}
}

bool C20::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C20--------------------------------------*/
/*------------------------------------C21--------------------------------------*/

C21::C21()
{
	CurrentCost = OriginalCost = 6;
	CardID = 21;
	CardTypes.Add(1);
	CardRare = 2;
	CardName = Y::PrintText(TEXT("延山式：断骨"));
	BindMessage(TEXT("21"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成4点伤害和2层易伤"));
}

FText C21::LogDescript()
{
	return FText();
}

void C21::Play(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(4) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S2, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone5"));
		PlayMontage(GetMontageName());
	}
}

bool C21::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C21--------------------------------------*/
/*------------------------------------C22--------------------------------------*/

C22::C22()
{
	CurrentCost = OriginalCost = 6;
	CardID = 22;
	CardTypes.Add(1);
	CardRare = 2;
	CardName = Y::PrintText(TEXT("延山式：摧筋"));
	BindMessage(TEXT("22"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成4点伤害和2层虚弱"));
}

FText C22::LogDescript()
{
	return FText();
}

void C22::Play(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(4) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<WeakBuff>(2) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S2, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone14"));
		PlayMontage(GetMontageName());
	}
}

bool C22::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C22--------------------------------------*/
/*------------------------------------C23--------------------------------------*/

C23::C23()
{
	CurrentCost = OriginalCost = 10;
	CardID = 23;
	CardTypes.Add(1);
	CardRare = 3;
	CardName = Y::PrintText(TEXT("延山式：诸武精通"));
	BindMessage(TEXT("23"));
	CurrentCardDescribe = Y::PrintText(TEXT("对一个方向3格内敌人造成10点伤害，手牌，抽牌堆和弃牌堆每有1张【延山式】增加2点伤害"));
}

FText C23::LogDescript()
{
	return FText();
}

void C23::Play(bool Execute)
{
	int32 extra = 0;
	for (auto& p : Y::GetGameInfo()->InHandCards) {
		if (p->CardTypes.Contains(1)) {
			extra++;
		}
	}
	for (auto& p : Y::GetGameInfo()->ToDrawCards) {
		if (p->CardTypes.Contains(1)) {
			extra++;
		}
	}
	for (auto& p : Y::GetGameInfo()->ExhaustCards) {
		if (p->CardTypes.Contains(1)) {
			extra++;
		}
	}
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	int32 leftBorder, rightBorder;
	Border(Pos, 3, leftBorder, rightBorder, ToPos > Pos);
	for (int32 i = leftBorder; i <= rightBorder; i++)
	{
		if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter))
		{
			Y_StatusBar S{ Y::YMakeShared<DemageBuff>(10 + extra) };
			ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[i]->StandCharacter, S, Execute);
		}
	}
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone8"));
		PlayMontage(GetMontageName());
	}
}

bool C23::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 3) && GetFloor != Y::GetMainCharacter()->StandFloor;
}

/*------------------------------------C23--------------------------------------*/
/*------------------------------------C24--------------------------------------*/

C24::C24()
{
	CurrentCost = OriginalCost = 10;
	CardID = 24;
	CardTypes.Add(1);
	UsedType = 1;
	CardRare = 3;
	CardName = Y::PrintText(TEXT("延山式：爆发"));
	BindMessage(TEXT("24"));
	CurrentCardDescribe = Y::PrintText(TEXT("向一个方向打出手牌中所有的【延山式】"));
}

FText C24::LogDescript()
{
	return FText();
}

void C24::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ChPos = Y::GetChoosedFloor()->SerialNumber;
	int32 leftBorder, rightBorder;
	Border(Pos, 2, leftBorder, rightBorder, ChPos > Pos);
	auto TA = Y::GetGameInfo()->InHandCards;
	for (auto& p : TA) {
		if (p->CardTypes.Contains(1)) {
			if (ChPos > Pos)
			{
				for (int32 i = leftBorder; i <= rightBorder; i++)
				{
					if (p->AcceptFloor(Y::GetFloors()[i]))
					{
						p->Play(Execute);
						if (Execute)
							Y::GetGameInfo()->UseCard(p);
					}
				}
			}
			else
			{
				for (int32 i = rightBorder; i >= leftBorder; i--)
				{
					if (p->AcceptFloor(Y::GetFloors()[i]))
					{
						p->Play(Execute);
						if (Execute)
							Y::GetGameInfo()->UseCard(p);
					}
				}
			}
		}
	}
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone10"));
		PlayMontage(GetMontageName());
	}
}

bool C24::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && GetFloor != Y::GetMainCharacter()->StandFloor;
}

/*------------------------------------C24--------------------------------------*/
/*------------------------------------C25--------------------------------------*/

C25::C25()
{
	CurrentCost = OriginalCost = 5;
	CardID = 25;
	CardRare = 1;
	CardName = Y::PrintText(TEXT("防御"));
	BindMessage(TEXT("25"));
	CurrentCardDescribe = Y::PrintText(TEXT("增加6层护盾"));
}

FText C25::LogDescript()
{
	return FText();
}

void C25::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<ShieldBuff>(6) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone9"));
		PlayMontage(GetMontageName());
	}
}

bool C25::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

/*------------------------------------C25--------------------------------------*/
/*------------------------------------C26--------------------------------------*/

C26::C26()
{
	CurrentCost = OriginalCost = 3;
	CardID = 26;
	CardRare = 1;
	CardName = Y::PrintText(TEXT("过载思考"));
	BindMessage(TEXT("26"));
	CurrentCardDescribe = Y::PrintText(TEXT("自身增加2层灼烧，抽4张卡"));
}

FText C26::LogDescript()
{
	return FText();
}

void C26::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<BurnBuff>(2) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	DrawCard(4, Execute);
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call2"), Y::GetMainCharacter()->StandFloor, nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C26::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

/*------------------------------------C26--------------------------------------*/
/*------------------------------------C27--------------------------------------*/

C27::C27()
{
	CurrentCost = OriginalCost = 4;
	CardID = 27;
	CardRare = 1;
	CardName = Y::PrintText(TEXT("点火"));
	BindMessage(TEXT("27"));
	CurrentCardDescribe = Y::PrintText(TEXT("对敌人施加3层灼烧"));
}

FText C27::LogDescript()
{
	return FText();
}

void C27::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<BurnBuff>(3) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call2"), Y::GetMainCharacter()->StandFloor, Y::GetChoosedFloor());
		PlayMontage(GetMontageName());
	}
}

bool C27::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && IsEnemy(GetFloor);
}

/*------------------------------------C27--------------------------------------*/
/*------------------------------------C28--------------------------------------*/

C28::C28()
{
	CurrentCost = OriginalCost = 4;
	CardID = 28;
	CardRare = 1;
	CardName = Y::PrintText(TEXT("烈焰击"));
	BindMessage(TEXT("28"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成3+3分之灼烧层数伤害"));
}

FText C28::LogDescript()
{
	return FText();
}

void C28::Play(bool Execute)
{
	auto buff = Y::GetChoosedFloor()->StandCharacter->Buffs->FindType(5);
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(buff.Num() > 0 ? 3 + buff[0]->BuffCount / 2 : 3) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call3"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C28::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C28--------------------------------------*/
/*------------------------------------C29--------------------------------------*/

C29::C29()
{
	CurrentCost = OriginalCost = 8;
	CardID = 29;
	CardRare = 1;
	CardName = Y::PrintText(TEXT("火焰释放"));
	BindMessage(TEXT("29"));
	CurrentCardDescribe = Y::PrintText(TEXT("对3格内敌人施加3层灼烧"));
}

FText C29::LogDescript()
{
	return FText();
}

void C29::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	int32 leftBorder, rightBorder;
	Border(Pos, absPlus(ToPos - Pos), leftBorder, rightBorder, ToPos > Pos);
	for (int32 i = leftBorder; i <= rightBorder; i++)
	{
		if (IsValid(Y::GetFloors()[i]) && IsEnemy(Y::GetFloors()[i]))
		{
			Y_StatusBar S{ Y::YMakeShared<BurnBuff>(6) };
			ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[i]->StandCharacter, S, Execute);
		}
	}
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Shoot2"), Y::GetMainCharacter()->StandFloor, Y::GetChoosedFloor());
		PlayMontage(GetMontageName());
	}
}

bool C29::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 3) && GetFloor != Y::GetMainCharacter()->StandFloor;
}

/*------------------------------------C29--------------------------------------*/
/*------------------------------------C30--------------------------------------*/

C30::C30()
{
	CurrentCost = OriginalCost = 10;
	CardID = 30;
	UsedType = 3;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("掌握火势"));
	BindMessage(TEXT("30"));
	CurrentCardDescribe = Y::PrintText(TEXT("使用后，每次施加灼烧时灼烧层数+1"));
}

FText C30::LogDescript()
{
	return FText();
}

void C30::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() { BuffCount = 1; BuffID = 1030; TriggerCondition = BeginBuff; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(5);
			for (auto& p0 : TA)p0->BuffCount += BuffCount;
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone7"));
		PlayMontage(GetMontageName());
	}
}

bool C30::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

/*------------------------------------C30--------------------------------------*/
/*------------------------------------C31--------------------------------------*/

C31::C31()
{
	CurrentCost = OriginalCost = 5;
	CardID = 31;
	UsedType = 1;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("渐热"));
	BindMessage(TEXT("31"));
	CurrentCardDescribe = Y::PrintText(TEXT("施加2层灼烧，每次使用该卡层数+1"));
	num = 0;
}

void C31::BeginFighting()
{
	num = 0;
}

FText C31::LogDescript()
{
	return FText();
}

void C31::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<BurnBuff>(2 + num) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	num++;
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call2"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C31::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C31--------------------------------------*/
/*------------------------------------C32--------------------------------------*/

C32::C32()
{
	CurrentCost = OriginalCost = 8;
	CardID = 32;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("煽风点火"));
	BindMessage(TEXT("32"));
	CurrentCardDescribe = Y::PrintText(TEXT("移动2点，施加2层灼烧3次"));
}

FText C32::LogDescript()
{
	return FText();
}

void C32::Play(bool Execute)
{
	for (int32 i = 0; i < 3; i++)
	{
		Y_StatusBar S{ Y::YMakeShared<BurnBuff>(2) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	}
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call2"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C32::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && IsEnemy(GetFloor);
}

/*------------------------------------C32--------------------------------------*/
/*------------------------------------C33--------------------------------------*/

C33::C33()
{
	CurrentCost = OriginalCost = 5;
	CardID = 33;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("助长火势"));
	BindMessage(TEXT("33"));
	CurrentCardDescribe = Y::PrintText(TEXT("移动2格，施加4层灼烧，若目标有10层灼烧则抽4张卡"));
}

FText C33::LogDescript()
{
	return FText();
}

void C33::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<BurnBuff>(4) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	auto buff = Y::GetChoosedFloor()->StandCharacter->Buffs->FindType(5);
	if (buff.Num() > 0 && buff[0]->BuffCount >= 10)
		DrawCard(4, Execute);
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call2"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C33::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && IsEnemy(GetFloor);
}

/*------------------------------------C33--------------------------------------*/
/*------------------------------------C34--------------------------------------*/

C34::C34()
{
	CurrentCost = OriginalCost = 5;
	CardID = 34;
	CardRare = 1;
	CardName = Y::PrintText(TEXT("趁火打劫"));
	BindMessage(TEXT("34"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成4点伤害，若目标有灼烧再次造成4点伤害"));
}

FText C34::LogDescript()
{
	return FText();
}

void C34::Play(bool Execute)
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(4) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S1, Execute);
	if (buff.Num() > 0)
	{
		Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(4) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S2, Execute);
	}
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call3"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C34::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C34--------------------------------------*/
/*------------------------------------C35--------------------------------------*/

C35::C35()
{
	CurrentCost = OriginalCost = 8;
	CardID = 35;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("引火"));
	BindMessage(TEXT("35"));
	CurrentCardDescribe = Y::PrintText(TEXT("对3格内敌人施加2层着火"));
}

FText C35::LogDescript()
{
	return FText();
}

void C35::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<OnBurnBuff>(2) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call4"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C35::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 3) && IsEnemy(GetFloor);
}

/*------------------------------------C35--------------------------------------*/
/*------------------------------------C36--------------------------------------*/

C36::C36()
{
	CurrentCost = OriginalCost = 8;
	CardID = 36;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("燃烧"));
	BindMessage(TEXT("36"));
	CurrentCardDescribe = Y::PrintText(TEXT("对3格内敌人造成2层猛燃"));
}

FText C36::LogDescript()
{
	return FText();
}

void C36::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<MoreBurnBuff>(2) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call1"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C36::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 3) && IsEnemy(GetFloor);
}

/*------------------------------------C36--------------------------------------*/
/*------------------------------------C37--------------------------------------*/

C37::C37()
{
	CurrentCost = OriginalCost = 8;
	CardID = 37;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("火焰连打"));
	BindMessage(TEXT("37"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成2点伤害4次，1层灼烧4次"));
}

FText C37::LogDescript()
{
	return FText();
}

void C37::Play(bool Execute)
{
	for (int32 i = 0; i < 4; i++)
	{
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(2) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S1, Execute);
		Y_StatusBar S2{ Y::YMakeShared<BurnBuff>(1) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S2, Execute);
	}
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call1"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C37::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

/*------------------------------------C37--------------------------------------*/
/*------------------------------------C38--------------------------------------*/

C38::C38()
{
	CurrentCost = OriginalCost = 6;
	CardID = 38;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("助燃"));
	BindMessage(TEXT("38"));
	CurrentCardDescribe = Y::PrintText(TEXT("对3格内敌人，目标每有2层灼烧向其施加1层灼烧"));
}

FText C38::LogDescript()
{
	return FText();
}

void C38::Play(bool Execute)
{
	auto buff = Y::GetChoosedFloor()->StandCharacter->Buffs->FindType(5);
	if (buff.Num() >= 2)
	{
		Y_StatusBar S{ Y::YMakeShared<BurnBuff>(buff[0]->BuffCount / 2) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	}
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call2"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C38::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 3) && IsEnemy(GetFloor);
}

/*------------------------------------C38--------------------------------------*/
/*------------------------------------C39--------------------------------------*/

C39::C39()
{
	CurrentCost = OriginalCost = 5;
	CardID = 39;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("嗜火"));
	BindMessage(TEXT("39"));
	CurrentCardDescribe = Y::PrintText(TEXT("移动1格，目标每有3层灼烧增加1格"));
}

FText C39::LogDescript()
{
	return FText();
}

void C39::Play(bool Execute)
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ChPos = Y::GetChoosedFloor()->SerialNumber;
	int32 Instance = ChPos - Pos;
	int32 moveInstance = 1;
	int32 ToPos;
	auto buff = Y::GetChoosedFloor()->StandCharacter->Buffs->FindType(5);
	if (buff.Num() > 0)moveInstance += buff[0]->BuffCount / 3;
	if (moveInstance < absPlus(Instance))
	{
		if (ChPos > Pos)
		{
			Move(moveInstance, Execute);
			ToPos = Pos + moveInstance;
		}
		else
		{
			Move(-moveInstance, Execute);
			ToPos = Pos - moveInstance;
		}
	}
	else
	{
		if (ChPos > Pos)
		{
			Move(Instance - 1, Execute);
			ToPos = ChPos - 1;
		}
		else
		{
			Move(Instance + 1, Execute);
			ToPos = ChPos + 1;
		}
	}
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call1"), Y::GetMainCharacter()->StandFloor, nullptr);
		PlayMontage(GetMontageName(), Y::GetFloors()[ToPos]);
	}
}

bool C39::AcceptFloor(AY_Floor* GetFloor)
{
	return IsValid(GetFloor) && !IsBlocked(GetFloor) && IsEnemy(GetFloor);
}

/*------------------------------------C39--------------------------------------*/
/*------------------------------------C40--------------------------------------*/

C40::C40()
{
	CurrentCost = OriginalCost = 6;
	CardID = 40;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("以火作衣"));
	BindMessage(TEXT("40"));
	CurrentCardDescribe = Y::PrintText(TEXT("获得3格内敌人灼烧层数的护盾"));
}

FText C40::LogDescript()
{
	return FText();
}

void C40::Play(bool Execute)
{
	auto buff = Y::GetChoosedFloor()->StandCharacter->Buffs->FindType(5);
	if (buff.Num() > 0)
	{
		Y_StatusBar S{ Y::YMakeShared<ShieldBuff>(buff[0]->BuffCount) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	}
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone9"));
		PlayMontage(GetMontageName());
	}
}

bool C40::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 3) && IsEnemy(GetFloor);
}

/*------------------------------------C40--------------------------------------*/
/*------------------------------------C41--------------------------------------*/

C41::C41()
{
	CurrentCost = OriginalCost = 8;
	CardID = 41;
	CardName = Y::PrintText(TEXT("引燃"));
	BindMessage(TEXT("41"));
	CurrentCardDescribe = Y::PrintText(TEXT("对2格内敌人施加6层灼烧"));
}

FText C41::LogDescript()
{
	return FText();
}

void C41::Play(bool Execute)
{
	int32 ChPos = Y::GetChoosedFloor()->SerialNumber;
	int32 leftBorder, rightBorder;
	Border(ChPos, 2 - 1, leftBorder, rightBorder);
	for (int32 i = leftBorder; i <= rightBorder; i++)
	{
		if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter))
		{
			Y_StatusBar S{ Y::YMakeShared<BurnBuff>(6) };
			ExecuteAction(Y::GetMainCharacter(), Y::GetFloors()[i]->StandCharacter, S, Execute);
		}
	}
	if (Execute)
	{
		PlayMontage(GetMontageName());
	}
}

bool C41::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2);
}

/*------------------------------------C41--------------------------------------*/
/*------------------------------------C42--------------------------------------*/

C42::C42()
{
	CurrentCost = OriginalCost = 10;
	CardID = 42;
	UsedType = 3;
	CardRare = 3;
	CardName = Y::PrintText(TEXT("不息烈火"));
	BindMessage(TEXT("42"));
	CurrentCardDescribe = Y::PrintText(TEXT("所有人灼烧层数不会降低"));
}

FText C42::LogDescript()
{
	return FText();
}

void C42::Play(bool Execute)
{
	//Need Fix

	for (auto& p : Y::GetGameInfo()->LivingEnemys) {
		Y_StatusBar TS{ MakeShared<B11>() };
		ExecuteAction(GetOwner(), p->Owner, TS, Execute);
	}

	Y_StatusBar TS{ MakeShared<B11>() };
	ExecuteAction(GetOwner(), GetOwner(), TS, Execute);

	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone5"));
		PlayMontage(GetMontageName());
	}
}

bool C42::AcceptFloor(AY_Floor* GetFloor)
{
	return IsValid(GetFloor);
}

/*------------------------------------C42--------------------------------------*/
/*------------------------------------C43--------------------------------------*/

C43::C43()
{
	CurrentCost = OriginalCost = 8;
	CardID = 43;
	CardRare = 2;
	CardName = Y::PrintText(TEXT("引燃"));
	BindMessage(TEXT("43"));
	CurrentCardDescribe = Y::PrintText(TEXT("结算目标灼烧"));
}

FText C43::LogDescript()
{
	return FText();
}

void C43::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<BurstBurn>(1) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	if (Execute)
	{
		PlayNiagara(Execute, TEXT("Call2"), Y::GetChoosedFloor(), nullptr);
		PlayMontage(GetMontageName());
	}
}

bool C43::AcceptFloor(AY_Floor* GetFloor)
{
	return IsValid(GetFloor) && IsValid(GetFloor->StandCharacter);
}

/*------------------------------------C43--------------------------------------*/
/*------------------------------------C44--------------------------------------*/

C44::C44()
{
	CurrentCost = OriginalCost = 15;
	CardID = 44;
	CardRare = 3;
	CardName = Y::PrintText(TEXT("死亡莲华"));
	BindMessage(TEXT("44"));
	CurrentCardDescribe = Y::PrintText(TEXT("对所有目标使用【引燃】，若有目标死亡，则再次使用【死亡莲花】"));
}

FText C44::LogDescript()
{
	return FText();
}

void C44::Play(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TSharedPtr<Y_CardInfo> Card;
		TB(TSharedPtr<Y_CardInfo> ToGetCard) { BuffID = 1044; TriggerCondition = AfterKill; Card = ToGetCard; };
		virtual int32 execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)override {
			Card->Play(TryAttack);
			return 0;
		}
	};
	for (auto& ep : Y::GetGameInfo()->LivingEnemys) {
		Y_StatusBar TS{ Y::YMakeShared<BurstBurn>(1),MakeShared<TB>(SharedThis(this)) };
		ExecuteAction(GetOwner(), ep->Owner, TS, Execute);
	}
	if (Execute)
	{
		Y::GetMainCharacter()->PlayNiagara(1, TEXT("Bone5"));
		PlayMontage(GetMontageName());
	}
}

bool C44::AcceptFloor(AY_Floor* GetFloor)
{
	return IsValid(GetFloor);
}

/*------------------------------------C44--------------------------------------*/
/*------------------------------------C2001------------------------------------*/

C2001::C2001()
{
	CurrentCost = OriginalCost = 3;
	CardID = 2001;
	CardTypes.Add(10);
	CardName = Y::PrintText(TEXT("疑虑"));
	CurrentCardDescribe = Y::PrintText(TEXT("无效果"));
}

FText C2001::LogDescript()
{
	return FText();
}

bool C2001::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

/*------------------------------------C2001------------------------------------*/
/*------------------------------------C2002------------------------------------*/

C2002::C2002()
{
	CurrentCost = OriginalCost = 0;
	CardID = 2002;
	CardTypes.Add(10);
	CardName = Y::PrintText(TEXT("痛苦"));
	CurrentCardDescribe = Y::PrintText(TEXT("对自身造成3点伤害，自身造成的所有伤害-1"));
}

FText C2002::LogDescript()
{

	return FText();
}

void C2002::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(3) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	if (Execute)
	{
		PlayMontage(GetMontageName());
	}
}

bool C2002::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

void C2002::Drawed()
{
	class TB :public Y_Buff {
	public:
		TB() { BuffCount = 1; BuffID = 2002; TriggerCondition = BeginAttack; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto& p = ToBuffs.Buff[0];
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)p0->BuffCount -= BuffCount;
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, true);
}

void C2002::Leave()
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(2002);
	for (auto& p : buff) {
		p->RemoveFromCharacter();
	}
}

/*------------------------------------C2002------------------------------------*/
/*------------------------------------C2003------------------------------------*/

C2003::C2003()
{
	CurrentCost = OriginalCost = 3;
	CardID = 2003;
	CardTypes.Add(10);
	CardName = Y::PrintText(TEXT("愤怒"));
	CurrentCardDescribe = Y::PrintText(TEXT("造成3点伤害，将一张【愤怒】加入牌堆"));
}

FText C2003::LogDescript()
{

	return FText();
}

void C2003::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(3) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	Y::GetGameInfo()->InHandCards.Add(SharedThis(this));
	if (Execute)
	{
		PlayMontage(GetMontageName());
	}
}

bool C2003::AcceptFloor(AY_Floor* GetFloor)
{
	return IsEnemy(GetFloor) && CardRange(GetFloor, 1);
}

/*------------------------------------C2003------------------------------------*/
/*------------------------------------C2004------------------------------------*/

C2004::C2004()
{
	CurrentCost = OriginalCost = 0;
	CardID = 2004;
	CardTypes.Add(10);
	CardName = Y::PrintText(TEXT("晕眩"));
	CurrentCardDescribe = Y::PrintText(TEXT("无法打出"));
}

FText C2004::LogDescript()
{

	return FText();
}

bool C2004::AcceptFloor(AY_Floor* GetFloor)
{
	return false;
}

/*------------------------------------C2004------------------------------------*/
/*------------------------------------C2005------------------------------------*/

C2005::C2005()
{
	CurrentCost = OriginalCost = 5;
	CardID = 2005;
	CardTypes.Add(10);
	CardName = Y::PrintText(TEXT("羞耻"));
	CurrentCardDescribe = Y::PrintText(TEXT("在手牌中时所有卡牌消耗+1"));
}

FText C2005::LogDescript()
{

	return FText();
}

bool C2005::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

void C2005::Drawed()
{
	class TB :public Y_Buff {
	public:
		TB() {
			BuffID = 2005;
			TriggerCondition = BeginAction;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto& p = ToBuffs.Buff[0];
			p->BuffCount--;
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), GetOwner(), S, true);
}

void C2005::Leave()
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(2005);
	for (auto& p : buff) {
		p->RemoveFromCharacter();
	}
}

/*------------------------------------C2005------------------------------------*/
