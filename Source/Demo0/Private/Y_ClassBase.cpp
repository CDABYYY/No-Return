// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_ClassBase.h"
#include "Y_Character.h"
#include "Y_Fighting.h"
#include "CameraPawn.h"
#include "Y_EventWidget.h"
#include "Y_ChoiceWidget.h"
#include "Y_PlayerController.h"
#include "Y_Settle.h"
#include "Y_Trophy.h"
#include "Y_Equipment.h"
#include "Y_GameInstance.h"
#include "Y.h"

void LoadY_Base()
{
	Y::LoadBuff<DemageBuff>(3);
	Y::LoadBuff<MoveBuff>(2);
	Y::LoadBuff<BurnBuff>(5);
	Y::LoadBuff<ShieldBuff>(4);
	Y::LoadCard<NormalCard>(-1);
	Y::LoadCharacter<NormalEnemy>(-1);
	Y::LoadRoom<NormalRoom>(-2);
	Y::LoadRoom<EventRoom>(-1);
	Y::LoadFloor<NormalFloor>(1);

	Y::LoadRoom<NormalFightRoom>(-10);
	Y::LoadEquipment<NormalEquipment>(-1);

	//Temp
	for (int32 i = 1; i <= 3; i++) {
		Y::Levels[i]->CanInLevel = 1 << i;
		for (int32 j = 1; j <= 3; j++) {
			Y::Levels[i]->ThisLevelPopulations.Add(MakeShared<Y_LevelInfo::EnemyPopulation>(j, j * 3 - 2, j * 3 - 1, j * 3));
		}
	}
	for (int32 i = 1; i <= 67; i++)Y::Levels[0]->ThisLevelCards.Add(i);
	for (int32 i = 1; i <= 5; i++) {
		Y::Levels[0]->ThisLevelEquipments.Add(i * 4 - 3);
	}
}

MoveBuff::MoveBuff()
{
	BuffAsType = BuffID = 2;
	TriggerCondition = 0;
	BuffProperty = 2;
	BuffOrder = 0;
	BuffLevel = 0;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("移动"));
}

int32 MoveBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	return 0;
}

void MoveBuff::AddToCharacter(AY_Character* TargetCharacter, bool Execute)
{
	
}

FText MoveBuff::printBuff(bool PrintLog) const
{
	return Y::PrintText(TEXT("Move %d"), BuffCount);
}

PureDemageBuff::PureDemageBuff()
{
	BuffAsType = BuffID = 3;
	TriggerCondition = DetectDeath;
	BuffProperty = 1;
	BuffOrder = 0;
	BuffLevel = 0;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("伤害"));
}

int32 PureDemageBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if(ToCharacter->Health <= 0)
	{
		return BuffID;
	}
	return 0;
}

void PureDemageBuff::AddToCharacter(AY_Character* TargetCharacter, bool Execute)
{
	Y::Log(0, TEXT("Try AddToCharacter"));
	if(IsValid(TargetCharacter))
	{
		Y_Buff::AddToCharacter(TargetCharacter, Execute);
		if (Execute)
			TargetCharacter->Health -= BuffCount;
	}
}

DemageBuff::DemageBuff()
{
	BuffID = 31;
	BuffExtend.Add(BuffID);
}


BurnDemageBuff::BurnDemageBuff()
{
	BuffID = 32;
	BuffExtend.Add(BuffID);
}

ShieldBuff::ShieldBuff()
{
	BuffAsType = BuffID = 4;
	TriggerCondition = BeginInjured | AfterAttack | AfterMove;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = 20;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("护盾"));
}

int32 ShieldBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if(TryAttack)
	{
		if (ExecuteCondition == BeginInjured) {
			auto T = ToBuffs.FindBuffExtend(3);//DemageBuff.ID
			for (auto& p : T) {
				if (p->BuffCount < BuffCount) {
					BuffCount -= p->BuffCount;
					p->BuffCount = 0;
					p->Living = false;
				}
				else if (p->BuffCount == BuffCount) {
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
	BuffParams.Add(0.5);
	BuffParams.Add(1);
	BuffName = Y::PrintText(TEXT("灼烧"));
}

int32 BurnBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if(TryAttack){
		Y_StatusBar TS;
		TS.AddBuff(Y::YMakeShared<BurnDemageBuff>(BuffCount * BuffParams[1]));
		Y::ExecuteAction(OwnerCharacter, OwnerCharacter, TS, TEXT("Burn"), TryAttack);
		BuffCount = BuffParams[0] * BuffCount;
		if (BuffCount == 0)
			RemoveFromCharacter();
	}
	return 0;
}


FText BurnBuff::printBuff(bool PrintLog) const
{
	return Y::PrintText(TEXT("Burn %d"),BuffCount);
}

NormalCard::NormalCard()
{
	CurrentCost = OriginalCost = 5;
	CardID = -1;
	CardName = Y::PrintText(TEXT("Charge"));
	UsingMontageName = TEXT("2");
	CurrentCardDescribe  = Y::PrintText(TEXT("Move to Front of Enemy, Attack 5"));
	CurrentPointDescribe = Y::PrintText(TEXT("Move to Front, Attack 5"));
	FString Path = TEXT("/Script/Engine.Texture2D'/Game/Resource/Png/JayceStaticField.JayceStaticField'");
	UsingPicture = Y::LoadPicture(Path);
}

FText NormalCard::LogDescript()
{
	return FText();
}

void NormalCard::Play( bool Execute)
{

	int32 Pos = Y::GetMainCharacter()->StandFloor->SerialNumber;
	int32 ToPos = Y::GetChoosedFloor()->SerialNumber;
	if (IsValid(Y::GetChoosedFloor()->StandCharacter)) {
		if (ToPos < Pos)ToPos += 1;
		else ToPos -= 1;
	}
	PlayNiagara(TEXT("FireBall02"), Execute, ToPos);
	if(ToPos - Pos != 0)
	{
		Move(ToPos - Pos, Execute);
	}
	if (IsValid(Y::GetChoosedFloor()->StandCharacter) && Y::GetChoosedFloor()->StandCharacter != Y::GetMainCharacter()) {
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(5) };
		ExecuteAction(Y::GetMainCharacter(), Y::GetChoosedFloor()->StandCharacter, S1, Execute);
	}
	DrawCard(1, Execute);
	PlayMontage(Execute, ToPos);
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
	ActionID = -1;
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

void NormalAction::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * 1;
	if (ToPos >= 0 && ToPos < Y::GetFloors().Num() && IsValid(Y::GetFloors()[ToPos]) && !IsValid(Y::GetFloors()[ToPos]->StandCharacter)) {
		Move(GetOwner()->Facing * 1, Execute);
		if(Execute)
		PlayMontage(UsingMontageName, Y::GetFloors()[ToPos]);
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
	BindBlueprint = TEXT("Default");

	ActionType = 0;
	ActionValue = 0;
	ChoosedAction = 0;

	EnemyID = -1;
}

void NormalEnemy::EnemyDead()
{
}

NormalRoom::NormalRoom()
{
	RoomID = -2;
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

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[-1]->NewObject(), Y::GetFloors()[7]);
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();

	Y::GetGameInfo()->BeginFight();
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
	RoomID = -1;
	BelongLevel = 1;
}

FText EventRoom::GetDescribe()
{
	return Y::PrintText(TEXT("Normal Event"));
}

TSharedPtr<Y_RoomInfo> EventRoom::RoomClicked()
{
	Y::Log(0, TEXT("InEventRoom"));
	//Temp
	//Y::GetPlayer()->SetActorLocation(FVector(0, 0, 190));
	//Y::GetPlayer()->SetActorRotation(FRotator(0, 0, 0));
	ChangeEndType(2);
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
	}

	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[-1]->NewObject(), Y::GetFloors()[7]);
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	TC->Update();
	
	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("Event Room"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("Quit")), []() {}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("Add Equipment")), []() {Y::GetGameInfo()->AddEquipment(MakeShared<Y_Equipment>()); }));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("DrawCard")), []() {Y::GetGameInfo()->DrawCard(); }));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("Reload")), []() {},EP));
	Y::GetController()->BeginEvent(EP);

	return nullptr;
}

void EventRoom::LeaveRoom()
{
	ChangeEndType(3);
	auto EP = MakeShared<Y_EventInfo>();
	EP->Description = Y::PrintText(TEXT("Will End Room"));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("EndRoom")), []() {}));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("Get New Card")), []() { Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(CardTrophy::Share({ Y::CardClass[-1]->NewObject(), Y::CardClass[1]->NewObject(), Y::CardClass[-1]->NewObject(), Y::CardClass[-1]->NewObject() })); }));
	EP->Choices.Add(MakeShared<Y_ChoiceInfoL>(Y::PrintText(TEXT("Reload")), []() {}, EP));
	Y::GetController()->BeginEvent(EP);
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

void AttackAction::ActionExecute(bool Execute)
{
	int32 ToPos = GetOwner()->StandFloor->SerialNumber + GetOwner()->Facing * 1;
	if (ToPos >= 0 && ToPos < Y::GetFloors().Num() && IsValid(Y::GetFloors()[ToPos]) && IsValid(Y::GetFloors()[ToPos]->StandCharacter)) {
		Y_StatusBar S1{ Y::YMakeShared<DemageBuff>(5) };
		ExecuteAction(GetOwner(), Y::GetFloors()[ToPos]->StandCharacter, S1, Execute);
	}
	if(Execute)
	PlayMontage(UsingMontageName, Y::GetFloors()[ToPos]);
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

void NormalSkill::Play(bool Execute)
{
	if(Execute)
	while (Y::GetGameInfo()->InHandCards.Num() > 5) {
		Y::GetGameInfo()->UseCard(Y::GetGameInfo()->InHandCards[0],1);
	}
	DrawCard(2,Execute);
}

NormalEquipment::NormalEquipment()
{
	ELevel = 1;
}

void NormalEquipment::Play(bool Execute)
{
	Y_StatusBar TS{ Y::YMakeShared<DemageBuff>(ELevel * 5) };
	ExecuteAction(GetOwner(), Y::GetChoosedFloor()->StandCharacter, TS, Execute);
}

bool NormalEquipment::AcceptFloor(AY_Floor* GetFloor)
{
	int32 F = GetOwner()->StandFloor->SerialNumber;
	int32 T = GetFloor->SerialNumber;
	return(F + 2 <= T && F - 2 >= T && IsValid(GetFloor->StandCharacter) && GetFloor->StandCharacter != GetOwner());
}

TArray<TSharedPtr<class Y_Equipment>> NormalEquipment::Upgrade()
{
	auto TP = MakeShared<NormalEquipment>();
	TP->FromEquipment = AsShared();
	TP->ELevel = ELevel + 1;
	TArray< TSharedPtr<class Y_Equipment>> TA;
	TA.Add(TP);
	return TA;
}
WeakBuff::WeakBuff() {
	BuffAsType = BuffID = 6;
	TriggerCondition = Ticking | BeginAttack;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("虚弱"));
}


int32 WeakBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == Ticking) {
		BuffCount -= 1;
		if (BuffCount <= 0)RemoveFromCharacter();
	}
	else if (ExecuteCondition == BeginAttack) {
		auto PA = ToBuffs.FindBuffExtend(3);
		for (auto& p : PA) {
			p->BuffCount *= 0.75;
		}
	}
	return 0;
}

ExposeBuff::ExposeBuff() {
	BuffAsType = BuffID = 7;
	TriggerCondition = Ticking | BeginInjured;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("易伤"));
}


int32 ExposeBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == Ticking) {
		BuffCount -= 1;
		if (BuffCount <= 0)RemoveFromCharacter();
	}
	else if (ExecuteCondition == BeginInjured) {
		auto PA = ToBuffs.FindBuffExtend(3);
		for (auto& p : PA) {
			p->BuffCount *= 1.25;
		}
	}
	return 0;
}

NormalFightRoom::NormalFightRoom()
{
	RoomID = -10;
}

TSharedPtr<Y_RoomInfo> NormalFightRoom::RoomClicked()
{
	Y::GetPlayer()->SetActorLocation(FVector(0, 0, 190));
	Y::GetPlayer()->SetActorRotation(FRotator(0, 0, 0));
	int32 SpawnFloors = 8 + 6 * Y::getRandom();
	TArray<int32> CanSpawnFloors;
	for (int32 i = 0; i < SpawnFloors; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
		CanSpawnFloors.Add(i);
	}
	int32 SpawnedMain = 4 + 3 * Y::getRandom();
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[SpawnedMain]);

	int32 GetP = Y::GetGameInfo()->CurrentFloor + 2; 
	int32 OP = GetP;
	auto P = Y::getRandom(Y::GetGameInfo()->CurrentLevel->ThisLevelPopulations);
	while (GetP > 0) {
		auto EnemyType = Y::getRandom(P->Classes);
		if (GetP < EnemyType->CostLevel * 0.5) break;
		GetP -= EnemyType->CostLevel;
		int32 EnemyPos = CanSpawnFloors[Y::getRandom() * CanSpawnFloors.Num()];
		CanSpawnFloors.Remove(EnemyPos);

		auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[EnemyType->EnemyID]->NewObject(), Y::GetFloors()[EnemyPos]);
		TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
		TC->Update();
	}
	Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(CardTrophy::Share());
	Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(MoneyTrophy::Share(OP *(0.8 + Y::getRandom() * 0.4) * 3 + Y::GetGameInfo()->CurrentLevelNum * 10));
	if (GetP < 0 && Y::getRandom() < (float) - GetP * 2 / OP)
		Y::GetGameInfo()->SettleInfo->TrophyInfos.Add(EquipmentTrophy::Share());
	Y::GetGameInfo()->BeginFight();
	return nullptr;
}

OnBurnBuff::OnBurnBuff()
{
	BuffAsType = BuffID = 8;
	TriggerCondition = Ticking | BeginBuffed;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("着火"));
}

int32 OnBurnBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition == Ticking) {
		BuffCount -= 1;
		if (BuffCount <= 0)RemoveFromCharacter();
	}
	else if (ExecuteCondition == BeginBuffed) {
		auto TA = ToBuffs.FindType(5);
		for (auto& p : TA)p->BuffCount += 1;
	}
	return 0;
}

MoreBurnBuff::MoreBurnBuff()
{
	BuffAsType = BuffID = 9;
	TriggerCondition = Ticking;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("猛燃"));
}

int32 MoreBurnBuff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	BuffCount -= 1;
	if (BuffCount <= 0)RemoveFromCharacter();
	return 0;
}

//Need Fix
void MoreBurnBuff::AddToCharacter(AY_Character* TargetCharacter, bool Execute)
{
	if(IsValid(TargetCharacter)){
		Y_Buff::AddToCharacter(TargetCharacter, Execute);
		if (Execute)
		{
			auto TA = OwnerCharacter->Buffs->FindType(5);
			for (auto& p : TA)p->BuffParams[1] = 2;
		}
	}
}

void MoreBurnBuff::RemoveFromCharacter()
{
	auto TA = OwnerCharacter->Buffs->FindType(5);
	for (auto& p : TA)p->BuffParams[1] = 1;
	Y_Buff::RemoveFromCharacter();
}

HealthBuff::HealthBuff()
{
	BuffAsType = BuffID = 10;
	TriggerCondition = 0;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("治疗"));
}

void HealthBuff::AddToCharacter(AY_Character* TargetCharacter, bool Execute)
{
	if (TargetCharacter->CheckValid())
	{
		if (Execute)
			TargetCharacter->Health += BuffCount;
	}
}

NormalBossRoom::NormalBossRoom(int32 FinalBoosType)
{
	RoomID = 999;
	BossType = FinalBoosType;
}

TSharedPtr<Y_RoomInfo> NormalBossRoom::RoomClicked()
{
	Y::Log(0, TEXT("Begin Boss Fight"));
	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorClass[1]->NewObject(), i);
	}
	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);
	auto Boss = Y::GetGameInfo()->SpawnCharacter(Y::CharacterClass[BossType]->NewObject(), Y::GetFloors()[7]);
	Boss->Buffs->AddBuff(MakeShared<Y_BuffR>(this));
	Boss->Update();

	Y::GetGameInfo()->BeginFight();
	return nullptr;
}

void NormalBossRoom::LeaveRoom()
{
	DoToEndRoom();
	Y::GetGameInfo()->ForwardLevel();
}
