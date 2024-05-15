// Fill out your copyright notice in the Description page of Project Settings.


#include "S01.h"
#include "Y.h"
#include "Y_GameInstance.h"
#include "Y_Buff.h"
#include "Y_Character.h"
#include "Y_Floor.h"
#include "CameraPawn.h"
#include "Y_StatusBar.h"
#include "Y_ClassBase.h"
#include "Y_Fighting.h"
#include "S03.h"
#include "I01.h"
#include "S_Helper.h"

using namespace S;

GainBuff::GainBuff() {
	BuffAsType = BuffID = 20;
	TriggerCondition = BeginAttack | Ticking;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("增益"));
}

int32 GainBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == Ticking) {
		BuffCount -= 1;
		if (BuffCount <= 0)RemoveFromCharacter();
	}
	else if (ExecuteCondition == BeginAttack) {
		auto PA = ToBuffs.FindBuffExtend(3);
		for (auto& p : PA) {
			p->BuffCount *= 1.25;
		}
	}
	return 0;
}

SeriousBuff::SeriousBuff() {
	BuffAsType = BuffID = 21;
	TriggerCondition = BeginInjured | Ticking;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("重伤"));
}

int32 SeriousBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == BeginInjured)
	{
		auto TA = ToBuffs.FindBuffExtend(3);
		for (auto& p0 : TA)p0->BuffCount += BuffCount;
	}
	else if (ExecuteCondition == Ticking)
	{
		BuffCount -= 1;
		if (BuffCount == 0)
			RemoveFromCharacter();
	}
	return 0;
}

MoraleBuff::MoraleBuff() {//士气buff
	BuffAsType = BuffID = 22;
	TriggerCondition = BeginAttack | AfterAttack | AfterBuff | AfterDeath | Ticking;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("士气"));
}

int32 MoraleBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == BeginAttack)
	{
		auto TA = ToBuffs.FindBuffExtend(3);
		for (auto& p0 : TA)p0->BuffCount += BuffCount;
	}
	else if (ExecuteCondition == AfterAttack)
	{
		BuffCount += 2;
	}
	else if (ExecuteCondition == AfterBuff)
	{
		BuffCount += 1;
	}
	else if (ExecuteCondition == AfterDeath)
	{
		for (int32 i = 0; i < Y::GetFloors().Num(); i++)
		{
			if (IsEnemy(Y::GetFloors()[i]))
			{
				auto buff = Y::GetFloors()[i]->StandCharacter->Buffs->FindType(22);
				if (buff.Num() > 0)
				{
					buff[0]->BuffCount /= 2;
				}
			}
		}
	}
	else if (ExecuteCondition == Ticking)
	{
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(2 * BuffCount) };
		ExecuteAction(nullptr, ToCharacter, S1);
	}
	return 0;
}

OverBuff::OverBuff() {//过载buff
	BuffAsType = BuffID = 23;
	TriggerCondition = BeginAttack | BeginAction | Ticking;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("过载"));
}

int32 OverBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == BeginAttack)
	{
		if (BuffCount >= 3)
		{
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)
			{
				p0->BuffCount += BuffCount;
			}
		}
		if (BuffCount >= 9)
		{
			Y_StatusBar S1{ Y::YMakeShared<ExposeBuff>(1) };
			ExecuteAction(nullptr, ToCharacter, S1);
		}
	}
	else if (ExecuteCondition == BeginAction)
	{
		if (BuffCount >= 6)
		{
			auto& p = ToBuffs.Buff[0];
			if (p->BuffID != 20001)p->BuffCount -= 5;
		}
	}
	else if (ExecuteCondition == Ticking)
	{
		Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(BuffCount) };
		ExecuteAction(nullptr, ToCharacter, S2);
	}
	return 0;
}

S01::S01()
{
	OriginalCost = CurrentCost = 5;
	UsingMontageName = TEXT("1");
	ActionID = 1;
}

float S01::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 0;
	return 10 * DisMT;
}

void S01::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseMove"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 2;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S01::ActionExecute(bool Execute)
{
	DisMT = MaxDist(GetOwner()->StandFloor, 1, GetOwner()->Facing);
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Move(GetOwner()->Facing * DisMT, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		if(DisMT != 0)
		PlayMontage(UsingMontageName, Y::GetFloors()[ToPos]);
	}
}

S02::S02()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 4;
	UsingMontageName = TEXT("2");
	ActionID = 2;
}

float S02::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S02::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 4;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S02::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * 1;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S03::S03()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 6;
	UsingMontageName = TEXT("3");
	ActionID = 3;
}

float S03::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2 && OwnerEnemy->ActionCount % 2 == 0) return 30;
	return 0;
}

void S03::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 6;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S03::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S04::S04()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 4;
	UsingMontageName = TEXT("2");
	ActionID = 4;
}

float S04::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1 && OwnerEnemy->ActionCount % 3 == 0) return 30;
	return 0;
}

void S04::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 4;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S04::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S05::S05()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 4;
	UsingMontageName = TEXT("3");
	ActionID = 5;
}

float S05::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S05::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 2;
	OwnerEnemy->ActionValue = 4;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S05::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<WeakBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S06::S06()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 8;
	UsingMontageName = TEXT("2");
	ActionID = 6;
}

float S06::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4) return 45;
	return 0;
}

void S06::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 8;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S06::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S07::S07()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("3");
	ActionID = 7;
}

float S07::GetWeight()
{
	if (OwnerEnemy->ActionCount % 5 == 0) return 999;
	return 0;
}

void S07::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S07::ActionExecute(bool Execute)
{
	TArray<int32> AccPos;
	for (int32 pos = 0; pos < Y::GetFloors().Num(); pos++)
	{
		if (IsValid(Y::GetFloors()[pos]) && !IsValid(Y::GetFloors()[pos]->StandCharacter))
		{
			AccPos.Add(pos);
		}
	}
	int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
	float prob = Y::getRandom();
	if (prob < 0.5)
	{
		Y::GetGameInfo()->SpawnCharacter(MakeShared<cateran1>(), Y::GetFloors()[EnemyPos]);
	}
	else {
		Y::GetGameInfo()->SpawnCharacter(MakeShared<cateran2>(), Y::GetFloors()[EnemyPos]);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S08::S08()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 4;
	UsingMontageName = TEXT("2");
	ActionID = 8;
}

float S08::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor)) return 0;
	if (DisMT <= 2 && OwnerEnemy->ActionCount % 2 == 0)  return 30;
	return 0;
}

void S08::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 4;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S08::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S09::S09()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 5;
	UsingMontageName = TEXT("3");
	ActionID = 9;
}

float S09::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2) return 25;
	return 0;
}

void S09::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 2;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S09::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S10::S10()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("2");
	ActionID = 10;
}

float S10::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 3 && OwnerEnemy->ActionCount % 4 == 0) return 40;
	return 0;
}

void S10::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S10::ActionExecute(bool Execute)
{
	int32 left, right;
	TArray<int32> AccPos;
	Border(GetOwner()->StandFloor->SerialNumber, 3, left, right);
	int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(10) };
	ExecuteAction(GetOwner(), Y::GetFloors()[EnemyPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S11::S11()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 5;
	UsingMontageName = TEXT("3");
	ActionID = 11;
}

float S11::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S11::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S11::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<WeakBuff>(1) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S12::S12()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("2");
	ActionID = 12;
}

float S12::GetWeight()
{
	if (OwnerEnemy->ActionCount % 3 == 0)return 20;
	return 0;
}

void S12::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 2;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S12::ActionExecute(bool Execute)
{
	OwnerEnemy->AttackEnhance += 2;
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S13::S13()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 4;
	UsingMontageName = TEXT("3");
	ActionID = 13;
}

float S13::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor)) return 0;
	if (DisMT <= 2) return 25;
	return 0;
}

void S13::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S13::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, 2, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S14::S14()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 5;
	UsingMontageName = TEXT("4");
	ActionID = 14;
}

float S14::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 30;
	return 0;
}

void S14::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S14::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(1) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S15::S15()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 2;
	UsingMontageName = TEXT("2");
	ActionID = 15;
}

float S15::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S15::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S15::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 3; i++) {
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S16::S16()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("3");
	ActionID = 16;
}

float S16::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0)return 25;
	return 0;
}

void S16::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S16::ActionExecute(bool Execute)
{
	OwnerEnemy->AttackEnhance += 1;
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S17::S17()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 2;
	UsingMontageName = TEXT("2");
	ActionID = 17;
}

float S17::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S17::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S17::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(5) };
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	for (int32 i = 0; i < 3; i++) {
		Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S18::S18()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("3");
	ActionID = 18;
}

float S18::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0)return 30;
	return 0;
}

void S18::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S18::ActionExecute(bool Execute)
{
	OwnerEnemy->AttackEnhance += 1;
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(5) };
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S19::S19()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 5;
	UsingMontageName = TEXT("4");
	ActionID = 19;
}

float S19::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1 && OwnerEnemy->ActionCount % 3 == 0) return 25;
	return 0;
}

void S19::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S19::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S20::S20()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("2");
	ActionID = 20;
}

float S20::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (OwnerEnemy->ActionCount % 3 == 0) return 10 * DisMT + 10;
	return 0;
}

void S20::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S20::ActionExecute(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() { BuffName = Y::PrintText(TEXT("点拨"));; BuffID = 1101; TriggerCondition = BeginAttack; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)p0->BuffCount += BuffCount;
			return 0;
		}
	};
	int32 left, right;
	TArray<int32> AccPos;
	Border(GetOwner()->StandFloor->SerialNumber, 3, left, right);
	for (int32 i = left; i <= right; i++)
	{
		if (IsEnemy(Y::GetFloors()[i])) {
			AccPos.Add(i);
		}
	}
	int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(GetOwner(), Y::GetFloors()[EnemyPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S21::S21()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("3");
	ActionID = 21;
}

float S21::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 3) return 35;
	return 0;
}

void S21::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 2;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S21::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	class TB :public Y_Buff {
	public:
		TB() { BuffID = 1102; BuffName = Y::PrintText(TEXT("弱点揭露")); TriggerCondition = BeginInjured; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			if (ExecuteCondition == BeginInjured)
			{
				auto TA = ToBuffs.FindBuffExtend(3);
				for (auto& p0 : TA)p0->BuffCount += 1;
			}
			else if (ExecuteCondition == Ticking)
			{
				BuffCount -= 1;
				if (BuffCount == 0)
					RemoveFromCharacter();
			}
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S22::S22()
{
	OriginalCost = CurrentCost = 30;
	UsingMontageName = TEXT("4");
	ActionID = 22;
}

float S22::GetWeight()
{
	if (OwnerEnemy->ActionCount % 5 == 0) return 999;
	return 0;
}

void S22::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S22::ActionExecute(bool Execute)
{
	TArray<int32> AccPos;
	for (int32 pos = 0; pos < Y::GetFloors().Num(); pos++)
	{
		if (IsValid(Y::GetFloors()[pos]) && !IsValid(Y::GetFloors()[pos]->StandCharacter))
		{
			AccPos.Add(pos);
		}
	}
	int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
	float prob = Y::getRandom();
	if (prob < 0.5)
	{
		Y::GetGameInfo()->SpawnCharacter(MakeShared<disciple1>(), Y::GetFloors()[EnemyPos]);
	}
	else {
		Y::GetGameInfo()->SpawnCharacter(MakeShared<disciple2>(), Y::GetFloors()[EnemyPos]);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S23::S23()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 5;
	UsingMontageName = TEXT("2");
	ActionID = 23;
}

float S23::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (2 <= DisMT && DisMT <= 3) return 35;
	return 0;
}

void S23::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S23::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S24::S24()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 5;
	UsingMontageName = TEXT("3");
	ActionID = 24;
}

float S24::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1 && OwnerEnemy->ActionCount % 3 == 0) return 15;
	return 0;
}

void S24::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S24::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y::GetGameInfo()->ToDrawCards.Add(MakeShared<C2001>());
	Y::GetGameInfo()->ToDrawCards.Add(MakeShared<C2001>());
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S25::S25()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("4");
	ActionID = 25;
}

float S25::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 3 && OwnerEnemy->ActionCount % 4 == 0)return 10 * DisMT + 15;
	return 0;
}

void S25::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 20;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S25::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(20) };
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S26::S26()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 5;
	UsingMontageName = TEXT("5");
	ActionID = 26;
}

float S26::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2) return 25;
	return 0;
}

void S26::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S26::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 3; i++) {
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S27::S27()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 8;
	UsingMontageName = TEXT("6");
	ActionID = 27;
}

float S27::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2 && OwnerEnemy->ActionCount % 3 == 0) return 30;
	return 0;
}

void S27::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S27::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S28::S28()
{
	OriginalCost = CurrentCost = 25;
	UsingMontageName = TEXT("7");
	ActionID = 28;
}

float S28::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4 && OwnerEnemy->ActionCount % 5 == 0) return 999;
	return 0;
}

void S28::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 40;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S28::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(40) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S29::S29()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("2");
	ActionID = 29;
}

float S29::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1 && OwnerEnemy->ActionCount % 2 == 0) return 25;
	return 0;
}

void S29::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S29::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(10) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S30::S30()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("3");
	ActionID = 30;
}

float S30::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S30::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S30::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	class TB :public Y_Buff {
	public:
		TB() { BuffName = Y::PrintText(TEXT("流血")); BuffID = 1103; TriggerCondition = AfterAction | Ticking; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			if (ExecuteCondition == AfterAction)
			{
				Y_StatusBar S2{ Y::YMakeShared<PureDemageBuff>(2) };
				ExecuteAction(nullptr, ToCharacter, S2);
			}
			else if (ExecuteCondition == Ticking)
			{
				BuffCount -= 1;
				if (BuffCount == 0)
					RemoveFromCharacter();
			}
			return 0;
		}
	};
	Y_StatusBar S3{ Y::YMakeShared<TB>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S3, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S31::S31()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("2");
	ActionID = 31;
}

float S31::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S31::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S31::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(15) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<WeakBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S32::S32()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("3");
	ActionID = 32;
}

float S32::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1 && OwnerEnemy->ActionCount % 2 == 0) return 25;
	return 0;
}

void S32::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 2;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S32::ActionExecute(bool Execute)
{
	Y::GetGameInfo()->ToDrawCards.Add(MakeShared<C2001>());
	Y::GetGameInfo()->ToDrawCards.Add(MakeShared<C2001>());
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S33::S33()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 20;
	UsingMontageName = TEXT("2");
	ActionID = 33;
}

float S33::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2) return 25;
	return 0;
}

void S33::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 20;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S33::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S34::S34()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("3");
	ActionID = 34;
}

float S34::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (OwnerEnemy->ActionCount % 3 == 0)return 10 * DisMT + 20;
	return 0;
}

void S34::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S34::ActionExecute(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() { BuffName = Y::PrintText(TEXT("点拨")); BuffID = 1101; TriggerCondition = BeginAttack; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p0 : TA)p0->BuffCount += BuffCount;
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	for (int32 pos = 0; pos < Y::GetFloors().Num(); pos++)
	{
		if (IsEnemy(Y::GetFloors()[pos]))
		{
			ExecuteAction(GetOwner(), Y::GetFloors()[pos]->StandCharacter, S1, Execute);
		}
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S35::S35()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("4");
	ActionID = 35;
}

float S35::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (OwnerEnemy->ActionCount % 4 == 0)return 10 * DisMT + 25;
	return 0;
}

void S35::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S35::ActionExecute(bool Execute)
{
	for (int32 pos = 0; pos < Y::GetFloors().Num(); pos++)
	{
		if (IsEnemy(Y::GetFloors()[pos]))
		{
			Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(10) };
			ExecuteAction(GetOwner(), Y::GetFloors()[pos]->StandCharacter, S1, Execute);
		}
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S36::S36()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 10;
	UsingMontageName = TEXT("2");
	ActionID = 36;
}

float S36::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (DisMT <= 3) return 35;
	return 0;
}

void S36::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S36::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S37::S37()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("3");
	ActionID = 37;
}

float S37::GetWeight()
{
	if (OwnerEnemy->ActionCount % 3 == 0)return 999;
	return 0;
}

void S37::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S37::ActionExecute(bool Execute)
{
	int32 left, right;
	TArray<int32> AccPos;
	Border(GetOwner()->StandFloor->SerialNumber, 3, left, right);
	for (int32 i = left; i <= right; i++)
	{
		if (IsEnemy(Y::GetFloors()[i]) && i != GetOwner()->StandFloor->SerialNumber) {
			AccPos.Add(i);
		}
	}
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(15) };
	if (AccPos.Num() > 0)
	{
		int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
		ExecuteAction(GetOwner(), Y::GetFloors()[EnemyPos]->StandCharacter, S1, Execute);
	}
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S38::S38()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("2");
	ActionID = 38;
}

float S38::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (OwnerEnemy->ActionCount % 4 == 0)return 999;
	return 0;
}

void S38::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 2;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S38::ActionExecute(bool Execute)
{
	int32 left, right;
	TArray<int32> AccPos;
	Border(GetOwner()->StandFloor->SerialNumber, 3, left, right);
	for (int32 i = left; i <= right; i++)
	{
		if (IsEnemy(Y::GetFloors()[i]) && i != GetOwner()->StandFloor->SerialNumber) {
			AccPos.Add(i);
		}
	}
	Y_StatusBar S1{ Y::YMakeShared<GainBuff>(2) };
	Y_StatusBar S2{ Y::YMakeShared<HealthBuff>(2) };
	if (AccPos.Num() > 0)
	{
		int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
		ExecuteAction(GetOwner(), Y::GetFloors()[EnemyPos]->StandCharacter, S1, Execute);
		ExecuteAction(GetOwner(), Y::GetFloors()[EnemyPos]->StandCharacter, S2, Execute);
	}
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	ExecuteAction(GetOwner(), GetOwner(), S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S39::S39()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 8;
	UsingMontageName = TEXT("3");
	ActionID = 39;
}

float S39::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4) return 45;
	return 0;
}

void S39::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 2 * 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S39::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S40::S40()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 15;
	UsingMontageName = TEXT("2");
	ActionID = 40;
}

float S40::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2 && OwnerEnemy->ActionCount % 3 == 0) return 40;
	return 0;
}

void S40::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S40::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ShieldBuff>(10) };
	ExecuteAction(GetOwner(), GetOwner(), S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S41::S41()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 15;
	UsingMontageName = TEXT("3");
	ActionID = 41;
}

float S41::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (DisMT <= 3) return 35;
	return 0;
}

void S41::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S41::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(1) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S42::S42()
{
	OriginalCost = CurrentCost = 30;
	UsingMontageName = TEXT("4");
	ActionID = 42;
}

float S42::GetWeight()
{
	if (OwnerEnemy->ActionCount % 5 == 0)return 999;
	return 0;
}

void S42::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S42::ActionExecute(bool Execute)
{
	TArray<int32> AccPos;
	for (int32 pos = 0; pos < Y::GetFloors().Num(); pos++)
	{
		if (IsValid(Y::GetFloors()[pos]) && !IsValid(Y::GetFloors()[pos]->StandCharacter))
		{
			AccPos.Add(pos);
		}
	}
	int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
	Y::GetGameInfo()->SpawnCharacter(MakeShared<guard2>(), Y::GetFloors()[EnemyPos]);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S43::S43()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 15;
	UsingMontageName = TEXT("2");
	ActionID = 43;
}

float S43::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (DisMT <= 3) return 35;
	return 0;
}

void S43::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S43::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S44::S44()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("3");
	ActionID = 44;
}

float S44::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0)return 999;
	return 0;
}

void S44::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S44::ActionExecute(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() { BuffName = Y::PrintText(TEXT("欢呼")); BuffID = 1105; TriggerCondition = BeginAttack; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p : TA)p->BuffCount += 5 * BuffCount;
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S45::S45()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 15;
	UsingMontageName = TEXT("2");
	ActionID = 45;
}

float S45::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4) return 10 * DisMT + 5;
	return 0;
}

void S45::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 2 * 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S45::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S46::S46()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("3");
	ActionID = 46;
}

float S46::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S46::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 2;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S46::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	DisMT = MaxDist(GetOwner()->StandFloor, 1, GetOwner()->Facing * -1);
	Move(DisMT, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S47::S47()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("4");
	ActionID = 47;
}

float S47::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0)return 999;
	return 0;
}

void S47::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S47::ActionExecute(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() { BuffName = Y::PrintText(TEXT("欢呼")); BuffID = 1105; TriggerCondition = BeginAttack; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p : TA)p->BuffCount += 5 * BuffCount;
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S48::S48()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 10;
	UsingMontageName = TEXT("2");
	ActionID = 48;
}

float S48::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S48::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 3 * 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S48::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 3; i++)
	{
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S49::S49()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 10;
	UsingMontageName = TEXT("3");
	ActionID = 49;
}

float S49::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (1 < DisMT && DisMT <= 2 && OwnerEnemy->ActionCount % 2 == 0) return 25;
	return 0;
}

void S49::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 2 * 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S49::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 2; i++)
	{
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S50::S50()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("4");
	ActionID = 50;
}

float S50::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (DisMT <= 3 && OwnerEnemy->ActionCount % 3 == 0) return 35;
	return 0;
}

void S50::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S50::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S51::S51()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("5");
	ActionID = 51;
}

float S51::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0)return 999;
	return 0;
}

void S51::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S51::ActionExecute(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() { BuffName = Y::PrintText(TEXT("欢呼")); BuffID = 1105; TriggerCondition = BeginAttack; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p : TA)p->BuffCount += 5 * BuffCount;
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S52::S52()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("2");
	ActionID = 52;
}

float S52::GetWeight()
{
	if (OwnerEnemy->ActionCount % 5 == 0)return 999;
	return 0;
}

void S52::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S52::ActionExecute(bool Execute)
{
	OwnerEnemy->AttackEnhance += 2;
	Y_StatusBar S1{ Y::YMakeShared<HealthBuff>(20) };
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S53::S53()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("3");
	ActionID = 53;
}

float S53::GetWeight()
{
	if (OwnerEnemy->ActionCount % 43 == 0) return 666;
	return 0;
}

void S53::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 2;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S53::ActionExecute(bool Execute)
{
	auto buff = GetOwner()->Buffs->FindType(6);
	for (auto& p : buff) {
		p->RemoveFromCharacter();
	}
	auto buff1 = GetOwner()->Buffs->FindType(7);
	for (auto& p : buff1) {
		p->RemoveFromCharacter();
	}
	OwnerEnemy->AttackEnhance += 2;
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S54::S54()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("4");
	ActionID = 54;
}

float S54::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (DisMT <= 6 && OwnerEnemy->ActionCount % 3 == 0) return 65;
	return 0;
}

void S54::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S54::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 3; i++)
	{
		if (DisMT > 2)
		{
			Move(GetOwner()->Facing * 2, Execute);
			DisMT -= 2;
		}
		else if (DisMT == 2)
		{
			Move(GetOwner()->Facing * 1, Execute);
			Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
			ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
			DisMT -= 1;
		}
		else
		{
			Move(GetOwner()->Facing * 0, Execute);
			Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
			ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
		}
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[ToPos - GetOwner()->Facing * 1]);
	}
}

S55::S55()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 15;
	UsingMontageName = TEXT("5");
	ActionID = 55;
}

float S55::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 3) return 35;
	return 0;
}

void S55::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S55::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S56::S56()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 15;
	UsingMontageName = TEXT("2");
	ActionID = 56;
}

float S56::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (2 < DisMT && DisMT <= 3) return 35;
	return 0;
}

void S56::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S56::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S57::S57()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("3");
	ActionID = 57;
}

float S57::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2) return 25;
	return 0;
}

void S57::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 2 * 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S57::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 2; i++)
	{
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S58::S58()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("2");
	ActionID = 58;
}

float S58::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4) return 45;
	return 0;
}

void S58::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S58::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S59::S59()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("3");
	ActionID = 59;
}

float S59::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0) return 666;
	return 0;
}

void S59::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 2;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S59::ActionExecute(bool Execute)
{
	int32 left, right;
	Border(GetOwner()->StandFloor->SerialNumber, 3, left, right);
	TArray<int32> AccPos;
	Border(GetOwner()->StandFloor->SerialNumber, 3, left, right);
	for (int32 i = left; i <= right; i++)
	{
		if (IsEnemy(Y::GetFloors()[i])) {
			AccPos.Add(i);
		}
	}
	int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
	auto buff1 = Y::GetFloors()[EnemyPos]->StandCharacter->Buffs->FindType(6);
	auto buff2 = Y::GetFloors()[EnemyPos]->StandCharacter->Buffs->FindType(7);
	for (auto& p : buff1) {
		p->RemoveFromCharacter();
	}
	for (auto& p : buff2) {
		p->RemoveFromCharacter();
	}

	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S60::S60()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("4");
	ActionID = 60;
}

float S60::GetWeight()
{
	if (OwnerEnemy->ActionCount % 5 == 0) return 999;
	return 0;
}

void S60::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S60::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(15) };
	int32 left, right;
	Border(GetOwner()->StandFloor->SerialNumber, 1, left, right);
	for (int32 i = left; i <= right; i++)
	{
		if (IsEnemy(Y::GetFloors()[i]) && i != GetOwner()->StandFloor->SerialNumber)
		{
			ExecuteAction(GetOwner(), Y::GetFloors()[i]->StandCharacter, S1, Execute);
			break;
		}
	}
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S61::S61()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("2");
	ActionID = 61;
}

float S61::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0)return 666;
	return 0;
}

void S61::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S61::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<MoraleBuff>(5) };
	ExecuteAction(GetOwner(), GetOwner(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S62::S62()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("3");
	ActionID = 62;
}

float S62::GetWeight()
{
	if (OwnerEnemy->ActionCount % 5 == 0)return 999;
	return 0;
}

void S62::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 2;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S62::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<GainBuff>(2) };
	for (int32 i = 0; i < Y::GetFloors().Num(); i++)
	{
		if (IsEnemy(Y::GetFloors()[i]))
		{
			ExecuteAction(GetOwner(), Y::GetFloors()[i]->StandCharacter, S1, Execute);
		}
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S63::S63()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 10;
	UsingMontageName = TEXT("4");
	ActionID = 63;
}

float S63::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2) return 25;
	return 0;
}

void S63::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S63::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 3; i++) {
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S64::S64()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 15;
	UsingMontageName = TEXT("2");
	ActionID = 64;
}

float S64::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (DisMT == 3) return 40;
	return 0;
}

void S64::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S64::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<SeriousBuff>(1) };
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S65::S65()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 15;
	UsingMontageName = TEXT("3");
	ActionID = 65;
}

float S65::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 3 && OwnerEnemy->ActionCount % 3 == 0) return 35;
	return 0;
}

void S65::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S65::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<SeriousBuff>(3) };
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S66::S66()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("4");
	ActionID = 66;
}

float S66::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2) return 30;
	return 0;
}

void S66::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S66::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<SeriousBuff>(1) };
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 2; i++) {
		Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S2, Execute);
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S67::S67()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 5;
	UsingMontageName = TEXT("2");
	ActionID = 67;
}

float S67::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4 && OwnerEnemy->ActionCount % 3 == 0) return 50;
	return 0;
}

void S67::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S67::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S68::S68()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 5;
	UsingMontageName = TEXT("3");
	ActionID = 68;
}

float S68::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4 && OwnerEnemy->ActionCount % 4 == 0) return 50;
	return 0;
}

void S68::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S68::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<WeakBuff>(2) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S69::S69()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 5;
	UsingMontageName = TEXT("4");
	ActionID = 69;
}

float S69::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4) return 45;
	return 0;
}

void S69::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S69::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<SeriousBuff>(2) };
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 2; i++) {
		Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetMainCharacter(), S2, Execute);
		ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S70::S70()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("2");
	ActionID = 70;
}

float S70::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0)return 666;
	return 0;
}

void S70::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S70::ActionExecute(bool Execute)
{
	auto TA = Y::GetMainCharacter()->Buffs->FindBuffExtend(9);
	Y_StatusBar S1{ Y::YMakeShared<SeriousBuff>(TA[0]->BuffCount) };
	for (int32 i = 0; i < Y::GetFloors().Num(); i++)
	{
		if (IsEnemy(Y::GetFloors()[i]))
		{
			ExecuteAction(GetOwner(), Y::GetFloors()[i]->StandCharacter, S1, Execute);
		}
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S71::S71()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("3");
	ActionID = 71;
}

float S71::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 4 && OwnerEnemy->ActionCount % 3 == 0) return 45;
	return 0;
}

void S71::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S71::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<SeriousBuff>(1) };
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S2, Execute);
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S72::S72()
{
	OriginalCost = CurrentCost = 20;
	Hurt = 10;
	UsingMontageName = TEXT("4");
	ActionID = 72;
}

float S72::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S72::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S72::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<SeriousBuff>(1) };
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S2{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S2, Execute);
	ExecuteAction(GetOwner(), Y::GetMainCharacter(), S1, Execute);
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing * -1);
	Move(DisMT, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S73::S73()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 15;
	UsingMontageName = TEXT("2");
	ActionID = 73;
}

float S73::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT == 3) { return 35; }
	return 0;
}

void S73::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 4;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S73::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<OverBuff>(1) };
	ExecuteAction(GetOwner(), GetOwner(), S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S74::S74()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 15;
	UsingMontageName = TEXT("3");
	ActionID = 74;
}

float S74::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2) return 25;
	return 0;
}

void S74::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 15;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S74::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<ShieldBuff>(10) };
	ExecuteAction(GetOwner(), GetOwner(), S2, Execute);
	Y_StatusBar S3{ Y::YMakeShared<OverBuff>(2) };
	ExecuteAction(GetOwner(), GetOwner(), S3, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S75::S75()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 10;
	UsingMontageName = TEXT("2");
	ActionID = 75;
}

float S75::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (IsBlocked(OwnerEnemy->Owner->StandFloor))return 0;
	if (DisMT <= 4 && OwnerEnemy->ActionCount % 4 == 0) return 45;
	return 0;
}

void S75::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 2;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S75::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	DisMT = MaxDist(GetOwner()->StandFloor, DisMT, GetOwner()->Facing);
	Move(DisMT, Execute);
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	Y_StatusBar S2{ Y::YMakeShared<OverBuff>(2) };
	ExecuteAction(GetOwner(), GetOwner(), S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[ToPos = GetOwner()->StandFloor->SerialNumber + DisMT]);
	}
}

S76::S76()
{
	OriginalCost = CurrentCost = 15;
	Hurt = 10;
	UsingMontageName = TEXT("3");
	ActionID = 76;
}

float S76::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 2 && OwnerEnemy->ActionCount % 3 == 0) return 25;
	return 0;
}

void S76::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 2 * 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S76::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	for (int32 i = 0; i < 2; i++)
	{
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(Hurt + OwnerEnemy->AttackEnhance) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	Y_StatusBar S2{ Y::YMakeShared<OverBuff>(2) };
	ExecuteAction(GetOwner(), GetOwner(), S2, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S77::S77()
{
	OriginalCost = CurrentCost = 15;
	UsingMontageName = TEXT("4");
	ActionID = 77;
}

float S77::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (DisMT <= 1) return 20;
	return 0;
}

void S77::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 10;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S77::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * DisMT;
	Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(10) };
	ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	int32 Dist = MaxDist(GetOwner()->StandFloor, 2, GetOwner()->Facing * -1);
	Move(Dist, Execute);
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName, Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + Dist]);
	}
}

S78::S78()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("2");
	ActionID = 78;
}

float S78::GetWeight()
{
	if (OwnerEnemy->ActionCount % 4 == 0) return 666;
	return 0;
}

void S78::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 3;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S78::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<OverBuff>(3) };
	for (int32 i = 0; i <= Y::GetFloors().Num(); i++)
	{
		if (IsEnemy(Y::GetFloors()[i])) {
			ExecuteAction(GetOwner(), Y::GetFloors()[i]->StandCharacter, S1, Execute);
		}
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S79::S79()
{
	OriginalCost = CurrentCost = 30;
	UsingMontageName = TEXT("3");
	ActionID = 79;
}

float S79::GetWeight()
{
	if (OwnerEnemy->ActionCount % 5 == 0)return 777;
	return 0;
}

void S79::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 3;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S79::ActionExecute(bool Execute)
{
	TArray<int32> AccPos;
	for (int32 pos = 0; pos < Y::GetFloors().Num(); pos++)
	{
		if (IsValid(Y::GetFloors()[pos]) && !IsValid(Y::GetFloors()[pos]->StandCharacter))
		{
			AccPos.Add(pos);
		}
	}
	int32 EnemyPos = Y::GetRandomArray(AccPos, 1)[0];
	float prob = Y::getRandom();
	if (prob < 0.5)
	{
		Y::GetGameInfo()->SpawnCharacter(MakeShared<lifeguard1>(), Y::GetFloors()[EnemyPos]);
	}
	else {
		Y::GetGameInfo()->SpawnCharacter(MakeShared<lifeguard2>(), Y::GetFloors()[EnemyPos]);
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S80::S80()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("4");
	ActionID = 80;
}

float S80::GetWeight()
{
	DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	DisMT = absPlus(DisMT);
	if (OwnerEnemy->ActionCount % 3 == 0) return 888;
	return 0;
}

void S80::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 20;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S80::ActionExecute(bool Execute)
{
	Y_StatusBar S1{ Y::YMakeShared<ShieldBuff>(20) };
	for (int32 i = 0; i < Y::GetFloors().Num(); i++)
	{
		if (IsEnemy(Y::GetFloors()[i]))
		{
			ExecuteAction(GetOwner(), Y::GetFloors()[i]->StandCharacter, S1, Execute);
		}
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}

S81::S81()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("5");
	ActionID = 81;
}

float S81::GetWeight()
{
	return 30;
}

void S81::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 3;
	OwnerEnemy->ActionValue = 3;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void S81::ActionExecute(bool Execute)
{
	class TB :public Y_Buff {
	public:
		TB() { BuffID = 1107; TriggerCondition = BeginAttack; }
		virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override {
			auto TA = ToBuffs.FindBuffExtend(3);
			for (auto& p : TA)p->BuffCount += 3 * BuffCount;
			return 0;
		}
	};
	Y_StatusBar S1{ Y::YMakeShared<TB>(1) };
	for (int32 i = 0; i < Y::GetFloors().Num(); i++)
	{
		if (IsEnemy(Y::GetFloors()[i]))
		{
			ExecuteAction(GetOwner(), Y::GetFloors()[i]->StandCharacter, S1, Execute);
		}
	}
	if (Execute)
	{
		OwnerEnemy->ActionCount++;
		PlayMontage(UsingMontageName);
	}
}
