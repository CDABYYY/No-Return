// Fill out your copyright notice in the Description page of Project Settings.
#include "I02.h"
#include "Y_ClassBase.h"
#include "Y_Character.h"
#include "Y_Fighting.h"
#include "Y_Equipment.h"
#include "Y.h"
#include "I_Helper.h"

using namespace I;

void L_I02()
{
	Y::LoadEquipment<EQ01>(1);
	Y::LoadEquipment<EQ02>(2);
	Y::LoadEquipment<EQ03>(3);
	Y::LoadEquipment<EQ04>(4);
	Y::LoadEquipment<EQ05>(5);
	Y::LoadEquipment<EQ06>(6);
	Y::LoadEquipment<EQ07>(7);
	Y::LoadEquipment<EQ08>(8);
	Y::LoadEquipment<EQ09>(9);
	Y::LoadEquipment<EQ10>(10);
	Y::LoadEquipment<EQ11>(11);
	Y::LoadEquipment<EQ12>(12);
	Y::LoadEquipment<EQ13>(13);
	Y::LoadEquipment<EQ14>(14);
	Y::LoadEquipment<EQ15>(15);
	Y::LoadEquipment<EQ16>(16);
	Y::LoadEquipment<EQ17>(17);
	Y::LoadEquipment<EQ18>(18);
	Y::LoadEquipment<EQ19>(19);
	Y::LoadEquipment<EQ20>(20);
}

bool NormalEQ::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}
/*------------------------------------EQ01--------------------------------------*/

EQ01::EQ01()
{
	EquipmentID = 1 + 1 * (1 << 10);
	EquipLevel = 1;
}

void EQ01::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<DemageBuff>(5) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS, Execute);
}

bool EQ01::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ01::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{MakeShared<EQ02>()};
}

/*------------------------------------EQ01--------------------------------------*/
/*------------------------------------EQ02--------------------------------------*/

EQ02::EQ02()
{
	EquipmentID = 1 + 2 * (1 << 10);
	EquipLevel = 2;
}

void EQ02::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<DemageBuff>(8) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS, Execute);
}

bool EQ02::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ02::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{MakeShared<EQ03>(), MakeShared<EQ04>()};
}

/*------------------------------------EQ02--------------------------------------*/

//ÖÆÊ½¸Ö½£
EQ03::EQ03()
{
	EquipmentID = 1 + 3 * (1 << 10) + 1 * (1 << 20);
	EquipLevel = 3;
}

void EQ03::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<DemageBuff>((Y::GetChoosedFloor()->StandCharacter->Health) * 0.1) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS, Execute);
}

bool EQ03::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ03::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}


//¸½Ä§½£
EQ04::EQ04()
{
	EquipmentID = 1 + 3 * (1 << 10) + 2 * (1 << 20);
	EquipLevel = 3;
}

void EQ04::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<DemageBuff>((Y::GetChoosedFloor()->StandCharacter->MaxHealth - Y::GetChoosedFloor()->StandCharacter->Health) * 0.1) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS, Execute);
}

bool EQ04::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ04::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}


//¹¦·¨Êé
EQ05::EQ05()
{
	EquipmentID = 2 + 1 * (1 << 10);
	EquipLevel = 1;
}

void EQ05::Play(bool Execute)
{
	DrawCard(2, Execute);
}

bool EQ05::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ05::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//×ÚÃÅÊÖ²á
EQ06::EQ06()
{
	EquipmentID = 2 + 2 * (1 << 10);
	EquipLevel = 2;
}

void EQ06::Play(bool Execute)
{
	DrawCard(3, Execute);
}

bool EQ06::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ06::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//°Ù¿ÆÈ«Êé
EQ07::EQ07()
{
	EquipmentID = 2 + 3 * (1 << 10) + 1 * (1 << 20);
	EquipLevel = 3;
}

void EQ07::Play(bool Execute)
{
	if (Y::GetGameInfo()->InHandCards.Num() < 6)
	{
		DrawCard(6 - Y::GetGameInfo()->InHandCards.Num(), Execute);
	}
}

bool EQ07::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ07::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//Ó¦¼±±¦µä
EQ08::EQ08()
{
	EquipmentID = 2 + 3 * (1 << 10) + 2 * (1 << 20);
	EquipLevel = 3;
}

void EQ08::Play(bool Execute)
{
	int getCardsnum = Y::GetGameInfo()->InHandCards.Num();
	for (auto& p : Y::GetGameInfo()->InHandCards)
	{
		Y::GetGameInfo()->UseCard(p, 1);
	}
	DrawCard(getCardsnum, Execute);
}

bool EQ08::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ08::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//·ÅÑªµ¶
EQ09::EQ09()
{
	EquipmentID = 3 + 1 * (1 << 10);
	EquipLevel = 1;
}

void EQ09::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<ExposeBuff>(1) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS, Execute);
}

bool EQ09::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ09::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//ÌÞ¹Çµ¶
EQ10::EQ10()
{
	EquipmentID = 3 + 2 * (1 << 10);
	EquipLevel = 2;
}

void EQ10::Play(bool Execute)
{
	Y_StatusBar TS1{ Y::YMakeShared<ExposeBuff>(1) };//Ò×ÉË
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS1, Execute);
	Y_StatusBar TS2{ Y::YMakeShared<WeakBuff>(1) };//ÐéÈõ
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS2, Execute);
}

bool EQ10::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ10::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//¾â¹Çµ¶
EQ11::EQ11()
{
	EquipmentID = 3 + 3 * (1 << 10) + 1 * (1 << 20);
	EquipLevel = 3;
}

void EQ11::Play(bool Execute)
{
	Y_StatusBar TS1{ Y::YMakeShared<ExposeBuff>(2) };//Ò×ÉË
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS1, Execute);
	Y_StatusBar TS2{ Y::YMakeShared<WeakBuff>(2) };//ÐéÈõ
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS2, Execute);
}

bool EQ11::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ11::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//´ÌÐÄµ¶
EQ12::EQ12()
{
	EquipmentID = 3 + 3 * (1 << 10) + 2 * (1 << 20);
	EquipLevel = 3;
}

void EQ12::Play(bool Execute)
{
	Y_StatusBar TS1{ Y::YMakeShared<ExposeBuff>(2) };//Ò×ÉË
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS1, Execute);
	//Ò×ÉËÊýÖµ·­±¶£¿£¿£¿£¿£¿£¿
}

bool EQ12::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ12::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//²¼¼×
EQ13::EQ13()
{
	EquipmentID = 4 + 1 * (1 << 10);
	EquipLevel = 1;
}

void EQ13::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<ShieldBuff>(5) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), TS, Execute);
}

bool EQ13::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ13::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//Ìú¼×
EQ14::EQ14()
{
	EquipmentID = 4 + 2 * (1 << 10);
	EquipLevel = 2;
}

void EQ14::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<ShieldBuff>(8) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), TS, Execute);
}

bool EQ14::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ14::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//º®Ìú¼×
EQ15::EQ15()
{
	EquipmentID = 4 + 3 * (1 << 10) + 1 * (1 << 20);
	EquipLevel = 3;
}

void EQ15::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<ShieldBuff>((Y::GetChoosedFloor()->StandCharacter->MaxHealth - Y::GetChoosedFloor()->StandCharacter->Health) * 0.3) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), TS, Execute);
}

bool EQ15::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ15::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//ÔÉÌú¼×
EQ16::EQ16()
{
	EquipmentID = 4 + 3 * (1 << 10) + 2 * (1 << 20);
	EquipLevel = 3;
}

void EQ16::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<ShieldBuff>((Y::GetChoosedFloor()->StandCharacter->MaxHealth) * 0.2) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), TS, Execute);
}

bool EQ16::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ16::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

/*------------------------------------EQ17--------------------------------------*/

EQ17::EQ17()
{
	EquipmentID = 5 + 1 * (1 << 10);
	EquipLevel = 1;
}

void EQ17::Play(bool Execute)
{

	class TB :public Y_Buff {
	public:
		TB() { BuffCount = 3; BuffID = 3017; TriggerCondition = BeginInjured; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)p0->BuffCount -= BuffCount;
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), GetOwner(), S, Execute);
}

bool EQ17::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ17::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

/*------------------------------------EQ17--------------------------------------*/
/*------------------------------------EQ18--------------------------------------*/

EQ18::EQ18()
{
	EquipmentID = 5 + 2 * (1 << 10);
	EquipLevel = 2;
}

void EQ18::Play(bool Execute)
{

	class TB :public Y_Buff {
	public:
		TB() { BuffCount = 5; BuffID = 3018; TriggerCondition = BeginInjured; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)p0->BuffCount -= BuffCount;
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), GetOwner(), S, Execute);
}

bool EQ18::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ18::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

/*------------------------------------EQ18--------------------------------------*/
/*------------------------------------EQ19--------------------------------------*/

EQ19::EQ19()
{
	EquipmentID = 5 + 3 * (1 << 10) + 1 * (1 << 20);
	EquipLevel = 3;
}

void EQ19::Play(bool Execute)
{

	class TB :public Y_Buff {
	public:
		TB() { BuffID = 3019; TriggerCondition = BeginInjured; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)
			{
				if (p0->BuffCount <= 10)
					p0->BuffCount = 0;
			}
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), GetOwner(), S, Execute);
}

bool EQ19::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ19::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

/*------------------------------------EQ19--------------------------------------*/
/*------------------------------------EQ20--------------------------------------*/

EQ20::EQ20()
{
	EquipmentID = 5 + 3 * (1 << 10) + 2 * (1 << 20);
	EquipLevel = 3;
}

void EQ20::Play(bool Execute)
{

	class TB :public Y_Buff {
	public:
		TB() { BuffID = 3020; TriggerCondition = BeginInjured; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)
			{
				p0->BuffCount *= 0.75;
			}
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), GetOwner(), S, Execute);
}

bool EQ20::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ20::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

/*------------------------------------EQ20--------------------------------------*/
/*------------------------------------EQ21--------------------------------------*/

EQ21::EQ21()
{
	EquipmentID = 6 + 1 * (1 << 10);
	EquipLevel = 1;
}

void EQ21::Play(bool Execute)
{

	class TB :public Y_Buff {
	public:
		TB() { BuffID = 3021; TriggerCondition = BeginInjured; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)
			{
				p0->BuffCount *= 0.75;
			}
			return 0;
		}
	};
	auto TP = MakeShared<TB>();
	Y_StatusBar S{ TP };
	ExecuteAction(Y::GetMainCharacter(), GetOwner(), S, Execute);
}

bool EQ21::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 0);
}

TArray<TSharedPtr<class Y_Equipment>> EQ21::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

/*------------------------------------EQ21--------------------------------------*/

EQ22::EQ22()
{
}

void EQ22::Play(bool Execute)
{
}

bool EQ22::AcceptFloor(AY_Floor* GetFloor)
{
	return false;
}

TArray<TSharedPtr<class Y_Equipment>> EQ22::Upgrade()
{
	return TArray<TSharedPtr<class Y_Equipment>>();
}



EQ23::EQ23()
{
}

void EQ23::Play(bool Execute)
{
}

bool EQ23::AcceptFloor(AY_Floor* GetFloor)
{
	return false;
}

TArray<TSharedPtr<class Y_Equipment>> EQ23::Upgrade()
{
	return TArray<TSharedPtr<class Y_Equipment>>();
}



EQ24::EQ24()
{
}

void EQ24::Play(bool Execute)
{
}

bool EQ24::AcceptFloor(AY_Floor* GetFloor)
{
	return false;
}

TArray<TSharedPtr<class Y_Equipment>> EQ24::Upgrade()
{
	return TArray<TSharedPtr<class Y_Equipment>>();
}



//×çÖä½£
EQ25::EQ25()
{
	EquipmentID = 7 + 1 * (1 << 10);
	EquipLevel = 1;
}

void EQ25::Play(bool Execute)
{
	if (Y::GetChoosedFloor()->StandCharacter->Health > 5)
	{
		Y::GetChoosedFloor()->StandCharacter->Health = Y::GetChoosedFloor()->StandCharacter->Health - 5;
	}
	else
	{
		Y::GetChoosedFloor()->StandCharacter->Health = 1;
	}
	Y_StatusBar TS{ Y::YMakeShared<DemageBuff>(10) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS, Execute);
}

bool EQ25::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ25::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//Öä½£
EQ26::EQ26()
{
	EquipmentID = 7 + 2 * (1 << 10);
	EquipLevel = 2;
}

void EQ26::Play(bool Execute)
{
	Y_StatusBar TS1{ Y::YMakeShared<DemageBuff>(8) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), TS1, Execute);
	Y_StatusBar TS2{ Y::YMakeShared<DemageBuff>(15) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS2, Execute);
}

bool EQ26::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ26::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//ÒûÑª½£
EQ27::EQ27()
{
	EquipmentID = 7 + 3 * (1 << 10) + 1 * (1 << 20);
	EquipLevel = 3;
}

void EQ27::Play(bool Execute)
{
	Y::GetChoosedFloor()->StandCharacter->Health = Y::GetChoosedFloor()->StandCharacter->Health + 8;
	Y_StatusBar TS{ Y::YMakeShared<DemageBuff>(15) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS, Execute);
}

bool EQ27::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ27::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>{};
}

//Áé½£
EQ28::EQ28()
{
	EquipmentID = 7 + 3 * (1 << 10) + 2 * (1 << 20);
	EquipLevel = 3;
}

void EQ28::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<DemageBuff>(8) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), TS, Execute);
	auto BS1 = Y::GetMainCharacter()->Buffs->FindType(7);
	for (auto& p : BS1)p->RemoveFromCharacter();
	auto BS2 = Y::GetMainCharacter()->Buffs->FindType(6);
	for (auto& p : BS2)p->RemoveFromCharacter();
}

bool EQ28::AcceptFloor(AY_Floor* GetFloor)
{
	return CardRange(GetFloor, 1) && IsEnemy(GetFloor);
}

TArray<TSharedPtr<class Y_Equipment>> EQ28::Upgrade()
{
	return TArray<TSharedPtr<Y_Equipment>>();
}


