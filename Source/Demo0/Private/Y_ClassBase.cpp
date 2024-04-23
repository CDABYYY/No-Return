// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_ClassBase.h"
#include "Y_Character.h"
#include "Y_Fighting.h"
#include "CameraPawn.h"
#include "Y_EventWidget.h"
#include "Y_ChoiceWidget.h"
#include "Y_PlayerController.h"
#include "Y.h"

void LoadY_Base()
{
	Y::LoadBuff<DemageBuff>(3);
	Y::LoadBuff<MoveBuff>(2);
	Y::LoadBuff<BurnBuff>(5);
	Y::LoadBuff<ShieldBuff>(4);
	Y::LoadCard<NormalCard>(1);
	Y::LoadCharacter<NormalEnemy>(1);
	Y::LoadRoom<NormalRoom>(1);
	Y::LoadFloor<NormalFloor>(1);
}

MoveBuff::MoveBuff()
{
	BuffAsType = BuffID = 2;
	TriggerCondition = 0;
	BuffProperty = 2;
	BuffOrder = 0;
	BuffLevel = 0;
	BuffExtend.Add(BuffID);
}

int32 MoveBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	return 0;
}

void MoveBuff::AddToCharacter(AY_Character* TargetCharacter)
{
	int32 ToSerial = TargetCharacter->StandFloor->SerialNumber + BuffCount;
	if (BuffCount == 0 || ToSerial < 0 || ToSerial > Y::GetFloors().Num() || Y::GetFloors()[ToSerial] == nullptr || IsValid(Y::GetFloors()[ToSerial]->StandCharacter)) {
		TargetCharacter->CharacterLogicalMove(Y::GetFloors()[ToSerial]);
	}
}

FText MoveBuff::printBuff(bool PrintLog) const
{
	return FText::FromString(FString::Printf(TEXT("Move %d"), BuffCount));
}

DemageBuff::DemageBuff()
{
	BuffAsType = BuffID = 3;
	TriggerCondition = DetectDeath;
	BuffProperty = 1;
	BuffOrder = 0;
	BuffLevel = 0;
	BuffExtend.Add(BuffID);
}

int32 DemageBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if(ToCharacter->Health <= 0)
	{
		return BuffID;
	}
	return 0;
}

void DemageBuff::AddToCharacter(AY_Character* TargetCharacter)
{
	Y_Buff::AddToCharacter(TargetCharacter);
	TargetCharacter->Health -= BuffCount;
}

FText DemageBuff::printBuff(bool PrintLog) const
{
	return Y::PrintText(TEXT("Damage %d"), BuffCount);
}

ShieldBuff::ShieldBuff()
{
	BuffAsType = BuffID = 4;
	TriggerCondition = BeginInjured | AfterAttack | AfterMove;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = 20;
	BuffExtend.Add(BuffID);
}

int32 ShieldBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == BeginInjured) {
		auto T = ToBuffs.FindBuffExtend(3);//DemageBuff.ID
		for (auto& p : T) {
			if (p->BuffCount < BuffCount) {
				BuffCount -= p->BuffCount;
				p->BuffCount = 0;
				p->Living = false;
			}
			else if (p->BuffCount == BuffCount){
				p->BuffCount = 0;
				p->Living = false;
				BuffCount = 0;
				RemoveFromCharacter();
			}
			else {
				p->BuffCount -= BuffCount;
				BuffCount = 0;
				RemoveFromCharacter();
			}
		}
	}
	else if (ExecuteCondition == AfterAttack) {
		BuffCount = 0.5 * BuffCount;
		if (BuffCount == 0)
			RemoveFromCharacter();
	}
	else if (ExecuteCondition == AfterMove) {
		BuffCount = 0.25 * BuffCount;
		if (BuffCount == 0)
			RemoveFromCharacter();
	}
	return 0;
}


FText ShieldBuff::printBuff(bool PrintLog) const
{
	return Y::PrintText(TEXT("Shield %d"), BuffCount);
}

BurnBuff::BurnBuff()
{
	BuffAsType = BuffID = 5;
	TriggerCondition = Ticking;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -20;
	BuffExtend.Add(BuffID);
}

int32 BurnBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	Y_StatusBar TS;
	TS.AddBuff(Y::YMakeShared<DemageBuff>(BuffCount));
	Y::ExecuteAction(OwnerCharacter, OwnerCharacter, TS, TEXT("Burn"),TryAttack);
	BuffCount = 0.5 * BuffCount;
	if (BuffCount == 0)
		RemoveFromCharacter();
	return 0;
}


FText BurnBuff::printBuff(bool PrintLog) const
{
	return Y::PrintText(TEXT("Burn %d"),BuffCount);
}

NormalCard::NormalCard()
{
	CurrentCost = OriginalCost = 5;
	CardID = 1;
	CardName = Y::PrintText(TEXT("Charge"));
	UsingMontageName = TEXT("Attack4");
	CurrentCardDescribe  = Y::PrintText(TEXT("Move to Front of Enemy, Attack 5"));
	CurrentPointDescribe = Y::PrintText(TEXT("Move to Front, Attack 5"));
	FString Path = TEXT("/Script/Engine.Texture2D'/Game/Resource/Png/JayceStaticField.JayceStaticField'");
	UsingPicture = Y::LoadPicture(Path);
}

FText NormalCard::LogDescript()
{
	return FText();
}

void NormalCard::Play()
{
	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	if (IsValid(Y::GetChoosedFloor()->StandCharacter)) {
		if (ToPos < Pos)ToPos += 1;
		else ToPos -= 1;
	}
	if(ToPos - Pos != 0)
	{
		Y_StatusBar S{ Y::YMakeShared<MoveBuff>(ToPos - Pos) };
		Y::ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, TEXT("Charge Move"));
		Y::GetMainCharacter()->CharacterLogicalMove(Y::GetFloors()[ToPos]);
	}
	if (IsValid(Y::GetChoosedFloor()->StandCharacter) && Y::GetChoosedFloor()->StandCharacter != Y::GetMainCharacter()) {
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(5) };
		Y::ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S1, TEXT("Charge Attack"));
	}
	Y::GetMainCharacter()->MyPlayMontage(GetMontageName(), Y::GetFloors()[ToPos], GetRate(), true);
	Y::GetGameInfo()->DrawCard();
}

bool NormalCard::AcceptFloor(AY_Floor* GetFloor)
{
	int32 F = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 T = GetFloor->SerialNumber;
	//if (!IsValid(GetFloor->StandCharacter)) return false;
	if (F < T && F + 3 > T) {
		for (int i = F + 1; i < T; i++) {
			if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter)) {
				return false;
			}
		}
		return true;
	}
	if (F > T && F - 3 < T) {
		for (int32 i = F - 1; i >= T ; i--)
		{
			if (IsValid(Y::GetFloors()[i]) && IsValid(Y::GetFloors()[i]->StandCharacter)) {
				return false;
			}
		}
		return true;
	}
	return false;
}

FText NormalCard::GetCardDescribe()
{

	return Y::PrintText(TEXT("Move to Front of Enemy, Attack 5"));
}

FText NormalCard::GetPointDescribe()
{
	return Y::PrintText(TEXT("Move to Front, Attack 5"));
}

NormalAction::NormalAction()
{
	OriginalCost = CurrentCost = 10;
	UsingMontageName = TEXT("Move1");
	ActionID = 1;
}

float NormalAction::GetWeight()
{
	int32 DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	if (DisMT < 0)DisMT *= -1;
	if (DisMT <= 1)DisMT = 0;
	return 10 * DisMT;
}

void NormalAction::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseMove"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 2;
	OwnerEnemy->ActionValue = 1;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void NormalAction::ActionExecute()
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * 1;
	if (ToPos >= 0 && ToPos < Y::GetFloors().Num() && IsValid(Y::GetFloors()[ToPos]) && !IsValid(Y::GetFloors()[ToPos]->StandCharacter)) {
		Y_StatusBar S1{ Y::YMakeShared<MoveBuff>(GetOwner()->Facing * 1) };
		Y::ExecuteAction(GetOwner(), GetOwner(), S1, TEXT("AI Move"));
		GetOwner()->CharacterLogicalMove(Y::GetFloors()[ToPos]);
		GetOwner()->MyPlayMontage(UsingMontageName, Y::GetFloors()[ToPos], GetRate(), true);
	}
}

FText NormalAction::LogDescript()
{
	return Y::PrintText(TEXT("Move"));
}

NormalEnemy::NormalEnemy()
{
	MaxHealth = CurrentHealth = 30;
	EnemyLevel = 10;
	Actions.Add(Y::YMakeShared<NormalAction>(this));
	Actions.Add(Y::YMakeShared<AttackAction>(this));

	ActionType = 0;
	ActionValue = 0;
	ChoosedAction = 0;

	EnemyID = 1;
}

void NormalEnemy::EnemyDead()
{
}

NormalRoom::NormalRoom()
{
	RoomID = 1;
}

FText NormalRoom::GetDescribe()
{
	return Y::PrintText(TEXT("Normal Fight"));
}

TSharedPtr<Y_RoomInfo> NormalRoom::RoomClicked()
{
	Y::GetPlayer()->SetActorLocation(FVector(0, 0, 190));
	Y::GetPlayer()->SetActorRotation(FRotator(0, 0, 0));
	Y::GetPlayer()->ClickAble = false;

	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
	}

	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	Y::GetGameInfo()->DrawCard(5);
	return nullptr;
}

void NormalRoom::LeaveRoom()
{
}

float NormalRoom::GetWeight()
{
	return 10;
}

EventRoom::EventRoom()
{
	RoomID = 2;
}

FText EventRoom::GetDescribe()
{
	return Y::PrintText(TEXT("Normal Event"));
}

TSharedPtr<Y_RoomInfo> EventRoom::RoomClicked()
{
	Y::GetPlayer()->SetActorLocation(FVector(0, 0, 190));
	Y::GetPlayer()->SetActorRotation(FRotator(0, 0, 0));

	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
	}

	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[1]->NewObject(), Y::GetFloors()[7]);
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	Y::GetGameInfo()->DrawCard(5);
	
	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("Event Room"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("Quit"), []() {})));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("DrawCard"), []() {Y::GetGameInfo()->DrawCard(); })));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("Reload"), []() {},EP)));
	Y::GetController()->BeginEvent(EP);

	return nullptr;
}

void EventRoom::LeaveRoom()
{
}

NormalFloor::NormalFloor()
{
	FloorID = 1;
}

void NormalFloor::Pass(AY_Character* Character)
{
}

void NormalFloor::Enter(AY_Character* Character)
{
}

void NormalFloor::Leave(AY_Character* Character)
{
}

AttackAction::AttackAction()
{
	OriginalCost = CurrentCost = 20;
	UsingMontageName = TEXT("Attack1");
	ActionID = 2;
}

float AttackAction::GetWeight()
{
	int32 DisMT = OwnerEnemy->Owner->StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber;
	if (DisMT < 0) DisMT *= -1;
	if (DisMT <= 1) return 20;
	return 0;
}

void AttackAction::ActionChoosed()
{
	Y::Log(0, TEXT("ChooseAttack"));
	OwnerEnemy->Owner->CharacterStatus = ActionID;
	OwnerEnemy->ActionType = 1;
	OwnerEnemy->ActionValue = 5;
	GetOwner()->ChangeFacing(Y::GetMainCharacter()->StandFloor->SerialNumber - GetOwner()->StandFloor->SerialNumber);
}

void AttackAction::ActionExecute()
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * 1;
	if (ToPos >= 0 && ToPos < Y::GetFloors().Num() && IsValid(Y::GetFloors()[ToPos]) && IsValid(Y::GetFloors()[ToPos]->StandCharacter)) {
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(5) };
		Y::ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, TEXT("AI Attack"));
	}
	GetOwner()->MyPlayMontage(UsingMontageName, Y::GetFloors()[ToPos], GetRate(), true);
}

FText AttackAction::LogDescript()
{
	return FText();
}

NormalSkill::NormalSkill()
{
	CurrentCost = OriginalCost = 3;
	CardName = Y::PrintText(TEXT("Skill"));
	UsingMontageName = TEXT("AS");
}

void NormalSkill::Play()
{
	while (Y::GetGameInfo()->InHandCards.Num() > 5) {
		Y::GetGameInfo()->UseCard(Y::GetGameInfo()->InHandCards[0]->Owner);
	}
	Y::GetGameInfo()->DrawCard(2);
}
