#include "I_Level1.h"
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

void IL1()
{
	Y::LoadCard<I_C01>(2001);
	Y::LoadCard<I_C02>(2002);
	Y::LoadCard<I_C03>(2003);
	Y::LoadCard<I_C04>(2004);
	Y::LoadCard<I_C05>(2005);
	Y::LoadCard<I_C06>(2006);
	Y::LoadCard<I_C07>(2007);
	Y::LoadCard<I_C08>(2008);
	Y::LoadCard<I_C09>(2009);
	Y::LoadCard<I_C10>(2010);
	Y::LoadCard<I_C11>(2011);
	Y::LoadCard<I_C12>(2012);
	Y::LoadCard<I_C13>(2013);
	Y::LoadCard<I_C14>(2014);
	Y::LoadCard<I_C15>(2015);
	Y::LoadCard<I_C16>(2016);
	Y::LoadCard<I_C17>(2017);
	Y::LoadCard<I_C18>(2018);
	Y::LoadCard<I_C19>(2019);
	Y::LoadCard<I_C20>(2020);
}

I_C01::I_C01()
{
	CurrentCost = OriginalCost = 3;
	CardID = 2001;
	CardName = Y::PrintText(TEXT("I_C01"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack enemy 5"));
}

FText I_C01::LogDescript()
{
	return FText();
}

void I_C01::Play()
{
	Y_StatusBar S{ Y::YMakeShared<DemageBuff>(5) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, TEXT("NewDescription"));
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C01::AcceptFloor(AY_Floor* GetFloor)
{
	return IsValid(GetFloor->StandCharacter) && GetFloor != Y::GetMainCharacter()->StandFloor && CardRange(GetFloor, 1);
}

I_C02::I_C02()
{
	CurrentCost = OriginalCost = 3;
	CardID = 2002;
	CardName = Y::PrintText(TEXT("I_C02"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Shield self 6"));
}

FText I_C02::LogDescript()
{
	return FText();
}

void I_C02::Play()
{
	Y_StatusBar S{ Y::YMakeShared<ShieldBuff>(6) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, TEXT("NewDescription"));
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C02::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C03::I_C03()
{
	CurrentCost = OriginalCost = 2;
	CardID = 2003;
	CardName = Y::PrintText(TEXT("I_C03"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Draw Card 3, Burn self 2"));
}

FText I_C03::LogDescript()
{
	return FText();
}

void I_C03::Play()
{
	Y_StatusBar S{ Y::YMakeShared<BurnBuff>(2) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, TEXT("NewDescription"));
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
	Y::GetGameInfo()->DrawCard(3);
}

bool I_C03::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C04::I_C04()
{
	CurrentCost = OriginalCost = 4;
	CardID = 2004;
	CardName = Y::PrintText(TEXT("I_C04"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 2, Burn self 2"));
}

FText I_C04::LogDescript()
{
	return FText();
}

void I_C04::Play()
{
	Y_StatusBar S1{ Y::YMakeShared<BurnBuff>(2) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, TEXT("NewDescription"));
	int32 moveInstance = Y::GetChoosedFloor()->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	Y_StatusBar S2{ Y::YMakeShared<MoveBuff>(moveInstance) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S2, TEXT("NewDescription"));
	Y::GetMainCharacter()->CharacterLogicalMove(Y::GetChoosedFloor());
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), true);
}

bool I_C04::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2) && !IsBlocked(GetFloor);
}

I_C05::I_C05()
{
	CurrentCost = OriginalCost = 3;
	CardID = 2005;
	CardName = Y::PrintText(TEXT("I_C05"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn enemy 4"));
}

FText I_C05::LogDescript()
{
	return FText();
}

void I_C05::Play()
{
	Y_StatusBar S{ Y::YMakeShared<BurnBuff>(4) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, TEXT("NewDescription"));
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C05::AcceptFloor(AY_Floor* GetFloor)
{
	return IsValid(GetFloor->StandCharacter) && GetFloor != Y::GetMainCharacter()->StandFloor && CardRange(GetFloor, 2);
}

I_C06::I_C06()
{
	CurrentCost = OriginalCost = 4;
	CardID = 2006;
	CardName = Y::PrintText(TEXT("I_C06"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn all 5"));
}

FText I_C06::LogDescript()
{
	return FText();
}

void I_C06::Play()
{
	int32 leftBorder, rightBorder;
	int32 tempFloorNum = Y::GetChoosedFloor()->SerialNumber;
	Border(tempFloorNum, 2, leftBorder, rightBorder);
	for (int32 i = leftBorder; i <= rightBorder; i++)
	{
		if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter))
		{
			Y_StatusBar S{ Y::YMakeShared<BurnBuff>(5) };
			Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, TEXT("NewDescription"));
		}
	}
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C06::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 2);
}

I_C07::I_C07()
{
	CurrentCost = OriginalCost = 4;
	CardID = 2007;
	CardName = Y::PrintText(TEXT("I_C07"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack self burn_num/2, Shield self burn_num"));
}

FText I_C07::LogDescript()
{
	return FText();
}

void I_C07::Play()
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(buff.Num() > 0 ? buff[0]->BuffCount / 2 : 0) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, TEXT("NewDescription"));
	Y_StatusBar S2{ Y::YMakeShared<ShieldBuff>(buff.Num() > 0 ? buff[0]->BuffCount : 0) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S2, TEXT("NewDescription"));
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C07::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C08::I_C08()
{
	CurrentCost = OriginalCost = 4;
	CardID = 2008;
	CardName = Y::PrintText(TEXT("I_C08"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Attack all burn_num"));
}

FText I_C08::LogDescript()
{
	return FText();
}

void I_C08::Play()
{
	int32 leftBorder, rightBorder;
	int32 tempFloorNum = Y::GetMainCharacter()->StandFloor->SerialNumber;
	Border(tempFloorNum, 3, leftBorder, rightBorder);
	for (int32 i = leftBorder; i <= rightBorder; i++)
	{
		if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter) && i != tempFloorNum)
		{
			auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
			Y_StatusBar S{ Y::YMakeShared<DemageBuff>(buff.Num() > 0 ? buff[0]->BuffCount : 0) };
			Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, TEXT("NewDescription"));
		}
	}
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C08::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C09::I_C09()
{
	CurrentCost = OriginalCost = 5;
	CardID = 2009;
	CardName = Y::PrintText(TEXT("I_C09"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("burn_num maintain 3/4"));
}

FText I_C09::LogDescript()
{
	return FText();
}

void I_C09::Play()
{
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C09::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C10::I_C10()
{
	CurrentCost = OriginalCost = 5;
	CardID = 2010;
	CardName = Y::PrintText(TEXT("I_C10"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn self 4, Purge self negativity -5 or lower"));
}

FText I_C10::LogDescript()
{
	return FText();
}

void I_C10::Play()
{
	Y::GetMainCharacter()->Buffs->RemoveBuffLevel(-5);
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C10::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C11::I_C11()
{
	CurrentCost = OriginalCost = 5;
	CardID = 2011;
	CardName = Y::PrintText(TEXT("I_C11"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Move 4, Burn enemy 3"));
}

FText I_C11::LogDescript()
{
	return FText();
}

void I_C11::Play()
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	Y_StatusBar S1{ Y::YMakeShared<MoveBuff>(ToPos - Pos) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, TEXT("NewDescription"));
	Y::GetMainCharacter()->CharacterLogicalMove(Y::GetFloors()[ToPos]);
	if (Pos < ToPos)
	{
		for (int32 i = Pos + 1; i < ToPos; i++)
		{
			if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter))
			{
				Y_StatusBar S2{ Y::YMakeShared<BurnBuff>(3) };
				Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S2, TEXT("NewDescription"));
			}
		}
	}
	else
	{
		for (int32 i = Pos - 1; i > ToPos; i--)
		{
			if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter))
			{
				Y_StatusBar S2{ Y::YMakeShared<BurnBuff>(3) };
				Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S2, TEXT("NewDescription"));
			}
		}
	}
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), true);
}

bool I_C11::AcceptFloor(AY_Floor* GetFloor)
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	if (buff.Num() > 0 && buff[0]->BuffCount >= 6) return !IsValid(GetFloor->StandCharacter) && CardRange(GetFloor, 4);
	else return false;
}

I_C12::I_C12()
{
	CurrentCost = OriginalCost = 5;
	CardID = 2012;
	UsedType = 3;
	CardName = Y::PrintText(TEXT("I_C12"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Draw card 1 when burn_num 6 or move trigger"));
}

FText I_C12::LogDescript()
{
	return FText();
}

void I_C12::Play()
{
	class PowerBuff :public Y_Buff {
	public:
		PowerBuff() {
			BuffAsType = BuffID = 5;
			TriggerCondition = Ticking;
			BuffProperty = 3;
			BuffOrder = -1;
			BuffLevel = 100;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {

			auto A = Y::GetMainCharacter()->Buffs->FindType(5);
			if (A.Num() > 0 && A[0]->BuffCount > 6) {
				Y::GetGameInfo()->DrawCard();
			}
			return 0;
		}
		virtual FText printBuff(bool PrintLog = false)const override {
			return Y::PrintText(TEXT("Burn 6 Draw 1."));
		}
	};
	auto P = Y::YMakeShared<PowerBuff>();
	P->AddToCharacter(Y::GetMainCharacter());

	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C12::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C13::I_C13()
{
	CurrentCost = OriginalCost = 3;
	CardID = 2013;
	CardName = Y::PrintText(TEXT("I_C13"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Burn enemy burn_num"));
}

FText I_C13::LogDescript()
{
	return FText();
}

void I_C13::Play()
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	Y_StatusBar S{ Y::YMakeShared<BurnBuff>(buff.Num() > 0 ? buff[0]->BuffCount : 0) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, TEXT("NewDescription"));
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C13::AcceptFloor(AY_Floor* GetFloor)
{
	return IsValid(GetFloor) && IsValid(GetFloor->StandCharacter);
}

I_C14::I_C14()
{
	CurrentCost = OriginalCost = 5;
	CardID = 2014;
	CardName = Y::PrintText(TEXT("I_C14"));
	UsingMontageName = TEXT("Attack4");
	UsedType = 3;
	CurrentCardDescribe = Y::PrintText(TEXT("Attack with Burn 2"));
}

FText I_C14::LogDescript()
{
	return FText();
}

void I_C14::Play()
{
	class PowerBuff :public Y_Buff {
	public:
		PowerBuff() {
			BuffAsType = BuffID = 5;
			TriggerCondition = BeginAttack;
			BuffProperty = 3;
			BuffOrder = -1;
			BuffLevel = 100;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto A = ToBuffs.FindType(3);
			for (auto& p : A)ToBuffs.AddBuff(Y::YMakeShared<BurnBuff>(2));
			return 0;
		}
		virtual FText printBuff(bool PrintLog = false)const override {
			return Y::PrintText(TEXT("Append 2 Burn."));
		}
	};
	auto P = Y::YMakeShared<PowerBuff>();
	P->AddToCharacter(Y::GetMainCharacter());

	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C14::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C15::I_C15()
{
	CurrentCost = OriginalCost = 3;
	CardID = 2015;
	CardName = Y::PrintText(TEXT("I_C15"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Draw Card burn_num/3"));
}

FText I_C15::LogDescript()
{
	return FText();
}

void I_C15::Play()
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
	Y::GetGameInfo()->DrawCard(buff.Num() > 0 ? buff[0]->BuffCount / 3 : 0);
}

bool I_C15::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C16::I_C16()
{
	CurrentCost = OriginalCost = 4;
	CardID = 2016;
	CardName = Y::PrintText(TEXT("I_C16"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Draw Card burn_num/3"));
}

FText I_C16::LogDescript()
{
	return FText();
}

void I_C16::Play()
{
	for (int i = 0; i < 3; i++)
	{
		Y_StatusBar S{ Y::YMakeShared<DemageBuff>(2),Y::YMakeShared<BurnBuff>(1) };
		Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S, TEXT("NewDescription"));
	}
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C16::AcceptFloor(AY_Floor* GetFloor)
{
	return IsValid(GetFloor->StandCharacter) && GetFloor != Y::GetMainCharacter()->StandFloor && CardRange(GetFloor, 1);
}

I_C17::I_C17()
{
	CurrentCost = OriginalCost = 2;
	CardID = 2017;
	CardName = Y::PrintText(TEXT("I_C17"));
	UsingMontageName = TEXT("Attack4");
	UsedType = 1;
	CurrentCardDescribe = Y::PrintText(TEXT("Shield burn_num"));
}

FText I_C17::LogDescript()
{
	return FText();
}

void I_C17::Play()
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	Y_StatusBar S{ Y::YMakeShared<ShieldBuff>(buff.Num() > 0 ? buff[0]->BuffCount : 0) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, TEXT("NewDescription"));
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C17::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C18::I_C18()
{
	CurrentCost = OriginalCost = 6;
	CardID = 2018;
	CardName = Y::PrintText(TEXT("I_C18"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("Reduce burn_num 1 when Move 1"));
}

FText I_C18::LogDescript()
{
	return FText();
}

void I_C18::Play()
{
	int32 moveInstance = Y::GetChoosedFloor()->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	Y_StatusBar S1{ Y::YMakeShared<MoveBuff>(moveInstance) };
	Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S1, TEXT("NewDescription"));
	Y::GetMainCharacter()->CharacterLogicalMove(Y::GetChoosedFloor());

	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	int32 AbsMove = I::absPlus(moveInstance);
	for (auto& p : buff) {
		if (p->BuffCount <= AbsMove) {
			AbsMove -= p->BuffCount;
			p->BuffCount = 0;
			p->RemoveFromCharacter();
		}
		else {
			p->BuffCount -= AbsMove;
			break;
		}
	}
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), true);
}

bool I_C18::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 3) && !IsBlocked(GetFloor);
}

I_C19::I_C19()
{
	CurrentCost = OriginalCost = 2;
	CardID = 2019;
	CardName = Y::PrintText(TEXT("I_C19"));
	UsingMontageName = TEXT("Attack4");
	UsedType = 1;
	CurrentCardDescribe = Y::PrintText(TEXT("Settle and Move all burn_num"));
}

FText I_C19::LogDescript()
{
	return FText();
}

void I_C19::Play()
{
	auto buff = Y::GetMainCharacter()->Buffs->FindType(5);
	for (auto& p : buff) {
		p->execute(Y::GetMainCharacter(), Y::GetMainCharacter(), *Y::GetMainCharacter()->Buffs, Y_Buff::Ticking, TEXT("IC19"));
		p->RemoveFromCharacter();
	}
	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C19::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

I_C20::I_C20()
{
	CurrentCost = OriginalCost = 0;
	CardID = 2020;
	CardName = Y::PrintText(TEXT("I_C20"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe = Y::PrintText(TEXT("when Settle all burn_num+1"));
}

FText I_C20::LogDescript()
{
	return FText();
}

void I_C20::Play()
{
	class PowerBuff :public Y_Buff {
	public:
		PowerBuff() {
			BuffAsType = BuffID = -5;
			TriggerCondition = CharacterSpawn;
			BuffProperty = 3;
			BuffOrder = -1;
			BuffLevel = 100;
		}
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			class InPowerBuff :public Y_Buff {
			public:
				InPowerBuff() {
					BuffAsType = BuffID = -6;
					TriggerCondition = Ticking;
					BuffProperty = 3;
					BuffOrder = -1;
					BuffLevel = 100;
				}
				virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
					Y::YMakeShared<BurnBuff>(1)->AddToCharacter(OwnerCharacter);
					return 0;
				}
			};
			Y::YMakeShared<InPowerBuff>(1)->AddToCharacter(ToCharacter);
			return 0;
		}
		virtual FText printBuff(bool PrintLog = false)const override {
			return Y::PrintText(TEXT("Append 2 Burn."));
		}
	};
	Y::GetGameInfo()->ExecuteToAllCharacter(Y::YMakeShared<PowerBuff>());

	Y::GetMainCharacter()->MyPlayMontage(UsingMontageName, Y::GetChoosedFloor(), GetRate(), false);
}

bool I_C20::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}