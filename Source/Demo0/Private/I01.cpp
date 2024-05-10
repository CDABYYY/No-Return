// Fill out your copyright notice in the Description page of Project Settings.


#include "I01.h"

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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 5 damage"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 2"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 5 damage,if weak +5 damage"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Charge 2, Attack enemy 5 damage"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack 1 nearby enemies 4 damage"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 4 damage, Draw 1 card for every 2 damage"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Give 4 damage and 1 expose to enemies 2 ahead"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 10 damage, Draw card 3"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 1"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 4 damage, Go back 2"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Charge 2, Attack enemy 5 damage, every Use TimeCost -1"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 4 damage, put 1 self in ExhaustCard"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 2 damage 3 times, every Use damage +1"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("all CardType 1 TimeCost -1"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("all CardType 1 damage +1"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("every 2 Use CardType 1 Draw card 1"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 5, every Kill damage +2"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Charge 3, Attack enemy 5 damage, put 1 stun in DrawCard"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 5 damage 2 ahead"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 5 damage, Get 1 self damage +1, drop if don't Use next"));
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
		TB(TSharedPtr<Y_CardInfo> PC,C20* Get) {
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
	auto TP = MakeShared<TB>(AsShared(),this);
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5 + extra),TP };
	ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, Execute);
	Y::GetGameInfo()->InHandCards.Add(AsShared());
	if (Execute)
	{
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Give 4 damage and 2 expose to enemy"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Give 4 damage and 2 weak to enemy"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 10 damage 3 ahead, every CardType 1 damage +2"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Use all TypeCard 1 Cards in one direction"));
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
		if (Execute)
			Y::GetGameInfo()->UseCard(p, 1);
	}
	if (Execute)
	{
		PlayMontage(GetMontageName());
	}

	Y::GetGameInfo()->UseCard(AsShared(), 1);
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Sheild self 6"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn self 2, Draw card 4"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn enemy 3"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 3+burn_num/3 damage"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 3, Burn 6(last 3)"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn 1 extra 【Burn】 1"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn 2, 【Burn】+1 for each time"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 2, Burn 2*3"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 2, Burn 4, Draw card 4 when burn_num 10"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 4, Attack enemy 4 when burn_num >=1"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 3, 【fire】 2, 【Burn】+1 for each time when 【fire】"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 3, 【Fire】 2, Damage*2 when 【Fire】"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Damage 2*4, Burn 1*4"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 3, Burn 1 when there are 2 burn_num"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 1, Move 1 when there are 3 burn_num"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Shield self burn_num"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn 6 all"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("keep all burn_num up"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn right now"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("light, light again when enemy dies"));
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
		Y_StatusBar TS{ Y::YMakeShared<BurstBurn>(1),MakeShared<TB>(AsShared()) };
		ExecuteAction(GetOwner(), ep->Owner, TS, Execute);
	}
	if (Execute)
	{
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Cost 3"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack self 3 damege,All Cards damage -1 when this in hand"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 3 damage, Get self again"));
}

FText C2003::LogDescript()
{

	return FText();
}

void C2003::Play(bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(3) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	Y::GetGameInfo()->InHandCards.Add(AsShared());
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Can't Use"));
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
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("all Cards TimeCost +1 when this in hand"));
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
