// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Fighting.h"
#include "Y_Equipment.h"
#include "Y_Floor.h"
#include "Y_Card.h"
#include "Y_Character.h"
#include "Y_GameInstance.h"
#include "CameraPawn.h"
#include "Y_CardInfo.h"
#include "Y_EnemyInfo.h"
#include "Y_Settle.h"
#include "Y_TimeLine.h"
#include "Y_PlayerController.h"
#include "Y_EquipmentH.h"
#include "Y_MapWidget.h"
#include "Y_CardH.h"
#include "Y_HUD.h"
#include "Y_TimeLine.h"
#include "Y_RoomWidget.h"
#include "Y.h"
#include "Y_ClassBase.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

Y_Fighting::Y_Fighting()
{
	CurrentLevelNum = 0;
	CurrentFloor = 0;
	Money = 200;
	Health = MaxHealth = 30;
	MCSkill = MakeShared<NormalSkill>();
}

Y_Fighting::~Y_Fighting()
{
}

void Y_Fighting::ExecuteToAllCharacter(TSharedPtr<class Y_Buff> ToExecuteBuff)
{
	ToExecuteBuff->execute(Y::GetMainCharacter(), Y::GetMainCharacter(), *Y::GetMainCharacter()->Buffs, Y_Buff::CharacterSpawn, TEXT("Spawn Execute"));
	for (auto& p : Y::GetEnemys()) {
		ToExecuteBuff->execute(p, p, *p->Buffs, Y_Buff::CharacterSpawn, TEXT("Spawn Execute"));
	}
	FightingBuffs.AddBuff(ToExecuteBuff);
}

void Y_Fighting::BeginRoom()
{
	SettleInfo = MakeShared<Y_SettleInfo>();
}

void Y_Fighting::BeginFight()
{
	EventBuffs.ExecuteBuffs(nullptr, nullptr, EventBuffs, Y_Buff::BeginFight, TEXT("Begin Fight"));
	AlwaysBuffs.ExecuteBuffs(nullptr, nullptr, AlwaysBuffs, Y_Buff::BeginFight, TEXT("Begin Fight"));
	FightingBuffs.ExecuteBuffs(nullptr, nullptr, FightingBuffs, Y_Buff::BeginFight, TEXT("Begin Fight"));
	//ToExecuteBuffs.ExecuteBuffs(nullptr, nullptr, ToExecuteBuffs, Y_Buff::BeginFight, TEXT("Begin Fight"));
	for (auto& p : Equipments) {
		p->BeginFighting();
	}

	for (auto& p : UsingCards) {
		p->BeginFighting();
		ToDrawCards.Add(p);
	}
	Y::GetGameInstance()->RunTime = 0;
	Y::GetGameInstance()->TickTime = 0;
	Y::GetPlayer()->ClickAble = false;

	Y::GetController()->ShowCards(false);
	DrawCard(5);
	Y::GetGameInstance()->MapSoundPlaying->Stop();
	Y::GetGameInstance()->MapSoundPlaying = UGameplayStatics::SpawnSound2D(Y::GetPlayer(), Y::GetGameInstance()->MapSound);
}

void Y_Fighting::AfterFight()
{
	FightingBuffs.ExecuteBuffs(nullptr, nullptr, FightingBuffs, Y_Buff::AfterFight, TEXT("After Fight"));
	AlwaysBuffs.ExecuteBuffs(nullptr, nullptr, AlwaysBuffs, Y_Buff::AfterFight, TEXT("After Fight"));
	EventBuffs.ExecuteBuffs(nullptr, nullptr, EventBuffs, Y_Buff::AfterFight, TEXT("After Fight"));
	FightingBuffs = Y_StatusBar();

	if (IsValid(Y::GetMainCharacter()))
	{
		Y::GetMainCharacter()->RemoveFromRoot();
		Y::GetMainCharacter()->Destroy();
	}
	Y::GetMainCharacter() = nullptr;
	for (auto& p : Y::GetEnemys())
	{
		if (p->CheckValid())
		{
			p->RemoveFromRoot();
			p->Destroy();
		}
	}
	Y::GetEnemys().Empty();

	for (auto& p : Y::GetFloors()) {
		if (IsValid(p))
		{
			p->RemoveFromRoot();
			p->Destroy();
		}
	}
	Y::GetFloors().Empty();

	//for (auto& p : Y::GetCards())if (IsValid(p))p->Destroy();
	//Y::GetCards().Empty();

	UY_TimeLine::YTimeLine->EndRoom();
	Y::GetController()->CardWidget->Clear();
	
	ToDrawCards.Empty();
	DiscardedCards.Empty();
	InHandCards.Empty();
	ExhaustCards.Empty();
	AppearedEnemys.Empty();
	LivingEnemys.Empty();

	Y::GetPlayer()->ClickAble = true;

	Y::GetGameInstance()->MapSoundPlaying->Stop();
	Y::GetGameInstance()->MapSoundPlaying  = UGameplayStatics::SpawnSound2D(Y::GetPlayer(), Y::GetGameInstance()->OpenMapSound);
}

void Y_Fighting::EndRoom()
{
	if(IsValid(Y::GetMainCharacter()))
	{
		Health = Y::GetMainCharacter()->Health;
		MaxHealth = Y::GetMainCharacter()->MaxHealth;
	}
	if(SettleInfo->TrophyInfos.Num() > 0)
	{
		Y::GetController()->ShowSettle(false);
		Y::GetController()->SettleWidget->LoadInfo(SettleInfo);
	}
	else {
		Y::GetGameInfo()->AfterFight();
		Y::GetController()->MapWidget->PullMap(false);
	}
}

void Y_Fighting::SpawnCharacter(AY_Character* SpawnedCharacter)
{
	EventBuffs.ExecuteBuffs(nullptr, SpawnedCharacter, EventBuffs, Y_Buff::CharacterSpawn, TEXT("Character Spawn"));
	AlwaysBuffs.ExecuteBuffs(nullptr, SpawnedCharacter, AlwaysBuffs, Y_Buff::CharacterSpawn, TEXT("Character Spawn"));
	FightingBuffs.ExecuteBuffs(nullptr, SpawnedCharacter, FightingBuffs, Y_Buff::CharacterSpawn, TEXT("Character Spawn"));
}

void Y_Fighting::AddEquipment(TSharedPtr<Y_Equipment> GetEquipment)
{
	Equipments.Add(GetEquipment);
	if (GetEquipment->FromEquipment != nullptr) {
		RemoveEquipment(GetEquipment->FromEquipment);
	}
	else {
		ReadyEquipments.Remove(GetEquipment);
	}
	GetEquipment->Equiped();
	Y::GetController()->PCHUD->EquipmentWidget->AddEquipment(GetEquipment);
}

void Y_Fighting::AddCard(TSharedPtr<class Y_CardInfo> GetCard)
{
	UsingCards.Add(GetCard);
	ReadyCards.Remove(GetCard);
	ReadyCards.Add(Y::CardClass[GetCard->CardID]->NewObject());
}

void Y_Fighting::RemoveEquipment(TSharedPtr<class Y_Equipment> GetEquipment)
{
	GetEquipment->UnEquiped();
	Equipments.Remove(GetEquipment);
	Y::GetController()->PCHUD->EquipmentWidget->RemoveEquipment(GetEquipment);
}

TArray<TSharedPtr<class Y_Equipment>> Y_Fighting::EquipmentUpgrades(int32 Level)
{
	TArray<TSharedPtr<Y_Equipment>> EA;
	for (auto& p : Equipments) {
		if(p->EquipLevel == Level)
		{
			EA.Append(p->Upgrade());
		}
	}
	return EA;
}

void Y_Fighting::AddMoney(int32 Moneys)
{
	//Y::GetGameInstance()->Money += Moneys;
	Money += Moneys;
}

int32& Y_Fighting::MoneyCount()
{
	//return Y::GetGameInstance()->Money;
	return Money;
}

void Y_Fighting::DrawCard(TSharedPtr<class Y_CardInfo> ToDrawCard, bool VoidSpawn)
{

	if(!VoidSpawn)
	{
		if (ToDrawCard == nullptr) {
			ToDrawCard = Y::getRandom(ToDrawCards);
		}
		ToDrawCards.Remove(ToDrawCard);
	}
	ToDrawCard->Drawed();
	InHandCards.Add(ToDrawCard);
	//SpawnCard(ToDrawCard);
	Y::GetController()->CardWidget->AddCard(ToDrawCard);
}

void Y_Fighting::DrawCard(int32 DrawCount)
{
	for (int32 i = 0; i < DrawCount; i++) {
		if (ToDrawCards.Num() == 0) {
			if (DiscardedCards.Num() == 0)break;
			for (auto& p : DiscardedCards) {
				ToDrawCards.Add(p);
			}
			DiscardedCards.Empty();
		}

		DrawCard(nullptr);
	}
}


void Y_Fighting::UseCard(AY_Card* UsedCard, int32 LeaveType)
{
	if (LeaveType != 0)
		UsedCard->Info->Discarded();
	UsedCard->Info->Leave();
	UsedCard->Info->Owner = nullptr;
	InHandCards.Remove(UsedCard->Info);
	if(UsedCard->Info->UsedType == 0)
	{
		DiscardedCards.Add(UsedCard->Info);
	}
	else if (UsedCard->Info->UsedType == 1) {
		ExhaustCards.Add(UsedCard->Info);
	}
	else if (UsedCard->Info->UsedType == 3) {

	}
	int32 pos = Y::GetCards().Find(UsedCard);
	if (pos >= 0)
	{
		Y::GetCards().RemoveAt(pos);
		for (int32 i = pos; i < Y::GetCards().Num(); i++)
		{
			if (IsValid(Y::GetCards()[i]))
				Y::GetCards()[i]->ToPosition -= 52;
		}
		UsedCard->Destroy();
	}
	Y::GetCards().Remove(UsedCard);
}

void Y_Fighting::UseCard(TSharedPtr<class Y_CardInfo> UsedCard, int32 DiscardReason)
{
	if (DiscardReason != 0)
	{
		UsedCard->Discarded();
		Y::GetController()->CardWidget->RemoveCard(UsedCard->OwnerWidget);
	}
	UsedCard->Leave();
	UsedCard->Owner = nullptr;
	InHandCards.Remove(UsedCard);
	if (UsedCard->UsedType == 0)
	{
		DiscardedCards.Add(UsedCard);
	}
	else if (UsedCard->UsedType == 1) {
		ExhaustCards.Add(UsedCard);
	}
	else if (UsedCard->UsedType == 3) {

	}
	//Y::GetController()->CardWidget->RemoveCard(UsedCard->OwnerWidget);
}

void Y_Fighting::PrepareDie(AY_Character* ToDieCharacter)
{
	UY_TimeLine::YTimeLine->RemoveCharacter(ToDieCharacter);
	LivingEnemys.Remove(ToDieCharacter->Info);
	Y::GetEnemys().Remove(ToDieCharacter);
}

void Y_Fighting::DestroyCharacter(AY_Character* ToDestroyCharacter)
{
	//Temp 
	ToDestroyCharacter->Destroy();
}

AY_Floor* Y_Fighting::SpawnFloor(TSharedPtr<class Y_FloorInfo> ToSpawnFloor, int32 SerialNumber, FName ActorClass)
{
	FVector ToVector(Y::GetLocation());
	FRotator ToRotator(Y::GetRotation());
	FVector RelativeVector(200, SerialNumber * 130, -100);
	RelativeVector = ToRotator.RotateVector(RelativeVector);
	FVector SpawnVector = Y::GetLocation() + RelativeVector;
	//ToRotator += FRotator(0, 90, 0);
	AY_Floor* NewFloor = Cast<AY_Floor>(Y::GetGameInstance()->GISpawnActor(2, ActorClass, SpawnVector, ToRotator));
	//AY_Floor* NewFloor = Cast<AY_Floor>(Y::GetWorld()->SpawnActor(Y::GetGameInstance()->FloorClasses.Find(ActorClass)->Get(), &SpawnVector, &ToRotator));
	NewFloor->SerialNumber = SerialNumber;
	for (int32 i = Y::GetFloors().Num(); i <= SerialNumber; i++) {
		Y::GetFloors().Add(nullptr);
	}
	Y::GetFloors()[SerialNumber] = NewFloor;
	NewFloor->Info = ToSpawnFloor;
	ToSpawnFloor->Owner = NewFloor;
	//NewFloor->AddToRoot();
	return NewFloor;
}

AY_Card* Y_Fighting::SpawnCard(TSharedPtr<class Y_CardInfo> ToSpawnCard, FName ActorClass)
{
	FVector AF = Y::GetPlayer()->MyCamera->GetComponentLocation();
	AF += FVector(270, -208 + 52 * 15, -90);//Base Location
	//AY_Card* NewCharacter = Cast<AY_Card>(Y::GetGameInstance()->GISpawnActor(3, ActorClass, SpawnVector, ToRotator));
	AY_Card* NewCard = Cast<AY_Card>(Y::GetWorld()->SpawnActor(Y::GetGameInstance()->CardClasses.Find(ActorClass)->Get(), &AF));
	NewCard->ToPosition = Y::GetCards().Num() * 52;
	NewCard->NowPosition = -4 * 52 + 15 * 52;
	ToSpawnCard->Owner = NewCard;
	NewCard->Info = ToSpawnCard;
	NewCard->Init();
	Y::GetCards().Add(NewCard);
	InHandCards.Add(ToSpawnCard);
	return NewCard;
}

AY_Character* Y_Fighting::SpawnCharacter(TSharedPtr<Y_EnemyInfo> ToSpawnCharacter, AY_Floor* FromFloor, FName ActorClass)
{
	if (ActorClass == TEXT("Default"))ActorClass = ToSpawnCharacter->BindBlueprint;
	FRotator ToRotator(Y::GetRotation());
	if (FromFloor->SerialNumber < Y::GetMainCharacter()->StandFloor->SerialNumber)
		ToRotator += FRotator(0, 90, 0);
	else 
		ToRotator += FRotator(0, -90, 0);
	FVector SpawnVector = FromFloor->TargetLocation();
	Y::Log(TEXT("Spawn Class: %s"), *(ActorClass.ToString()));
	AY_Character* NewCharacter = Cast<AY_Character>(Y::GetGameInstance()->GISpawnActor(1, ActorClass, SpawnVector, ToRotator));
	//AY_Character* NewCharacter = Cast<AY_Character>(Y::GetWorld()->SpawnActor(Y::GetGameInstance()->EnemyClasses.Find(ActorClass)->Get(), &SpawnVector, &ToRotator));
	NewCharacter->StandFloor = FromFloor;
	FromFloor->StandCharacter = NewCharacter;
	if (FromFloor->SerialNumber > Y::GetMainCharacter()->StandFloor->SerialNumber)
	{
		NewCharacter->Facing = -1;
		NewCharacter->Rotating = -90;
	}
	NewCharacter->Health = ToSpawnCharacter->CurrentHealth;
	NewCharacter->MaxHealth = ToSpawnCharacter->MaxHealth;
	NewCharacter->Info = ToSpawnCharacter;
	NewCharacter->LoadInfo(ToSpawnCharacter);
	ToSpawnCharacter->Owner = NewCharacter;
	ToSpawnCharacter->LoadCharacter(NewCharacter);
	Y::GetEnemys().Add(NewCharacter);
	LivingEnemys.Add(ToSpawnCharacter);
	AppearedEnemys.Add(ToSpawnCharacter);
	SpawnCharacter(NewCharacter);
	//NewCharacter->AddToRoot();
	return NewCharacter;
}

AY_Character* Y_Fighting::SpawnMC(AY_Floor* FromFloor, FName ActorClass)
{
	FRotator ToRotator(Y::GetRotation());
	ToRotator += FRotator(0, 90, 0);
	FVector SpawnVector = FromFloor->TargetLocation(); 
	AY_Character* NewCharacter = Cast<AY_Character>(Y::GetGameInstance()->GISpawnActor(0, ActorClass, SpawnVector, ToRotator));
	//AY_Character* NewCharacter = Cast<AY_Character>(Y::GetWorld()->SpawnActor(Y::GetGameInstance()->AllyClasses.Find(ActorClass)->Get(), &SpawnVector, &ToRotator));
	NewCharacter->StandFloor = FromFloor;
	FromFloor->StandCharacter = NewCharacter;
	Y::GetMainCharacter() = NewCharacter;
	SpawnCharacter(NewCharacter);
	NewCharacter->Health = Health;
	NewCharacter->MaxHealth = MaxHealth;
	NewCharacter->Buffs->AddBuffs(OnCharacterBuffs);
	return NewCharacter;
}

TSharedPtr<class Y_CardInfo> Y_Fighting::GetRandomCard()
{
	TMap<TSharedPtr<Y_CardInfo>, float> CardRates;
	for (auto& p : ReadyCards) {
		float RareRate = 1;
		if (p->CardRare == 1)RareRate = 9;
		if (p->CardRare == 2)RareRate = 3;
		CardRates.Add(p, RareRate);
	}
	auto p = Y::getRandom(CardRates);
	return p;
}

TSharedPtr<class Y_Equipment> Y_Fighting::GetRandomEquipment()
{
	auto p = Y::getRandom(ReadyEquipments);
	return p;
}

void Y_Fighting::LoadLevel(TSharedPtr<class Y_LevelInfo> ToLoadLevel)
{
	if (CurrentLevel.IsValid()) {
		CurrentLevel->UnLoad();
	}
	CurrentLevel = ToLoadLevel;
	CurrentLevel->Loaded();
	Y::GetController()->UpdateMap();
}

void Y_Fighting::ForwardLevel()
{
	CurrentLevelNum++;
	CurrentFloor = 0;
	auto P = Y::getRandom(Y::Levels);
	if (P.IsValid()) {
		Y::Log(TEXT("Load Level:%d"), P->LevelID);
		LoadLevel(P);
	}
}

float Y_LevelInfo::EnemyClass::GetWeight()
{
	return Weight;
}

Y_LevelInfo::EnemyClass::EnemyClass(int32 ThisEnemyID, int32 ThisPopulation, int32 ThisType, float ThisCostLevel, float ThisWeight)
{
	EnemyID = ThisEnemyID;
	Population = ThisPopulation;
	Type = ThisType;
	Weight = ThisWeight;
	CostLevel = ThisCostLevel;
}

Y_LevelInfo::Y_LevelInfo()
{
	Weight = 10;
	CanInLevel = 0;
}

Y_LevelInfo::~Y_LevelInfo()
{
}

float Y_LevelInfo::GetWeight()
{
	if ((1 << Y::GetGameInfo()->CurrentLevelNum) & CanInLevel) {
		return Weight;
	}
	return 0;
}

void Y_LevelInfo::Loaded()
{
	for (auto& i : ThisLevelCards)
		Y::GetGameInfo()->ReadyCards.Add(Y::CardClass[i]->NewObject());
	Y::GetGameInfo()->CanSpawnCards.Append(ThisLevelCards);
	for (auto& i : ThisLevelRooms) {
		if (!Y::RoomClass.Find(i))
			Y::Log(TEXT("UnFind this Room: %d"), i);
		Y::GetGameInfo()->ReadyRooms.Add(Y::RoomClass[i]->NewObject());
	}
	for (auto& i : ThisLevelEquipments) {
		Y::GetGameInfo()->ReadyEquipments.Add(Y::EquipmentClass[i]->NewObject());
	}

	if(LevelMusic)
	Y::GetGameInstance()->MapSound = LevelMusic;


	Y::Log(0, TEXT("Level:%d"), LevelID);
	Y::Log(0, TEXT("Level Position: %lf %lf %lf"), LevelLocation.X, LevelLocation.Y, LevelLocation.Z);
	Y::GetPlayer()->SetActorLocation(LevelLocation);
	Y::GetPlayer()->SetActorRotation(LevelRotation);

	Y::GetLocation() = LevelLocation;
	Y::GetRotation() = LevelRotation;
}

void Y_LevelInfo::UnLoad()
{
	Y::GetGameInfo()->ReadyRooms.RemoveAll([this](TSharedPtr<Y_RoomInfo> P) {return P->BelongLevel == LevelID; });
}

float Y_LevelInfo::EnemyPopulation::GetWeight()
{
	return Weight;
}

Y_LevelInfo::EnemyPopulation::EnemyPopulation()
{

}

Y_LevelInfo::EnemyPopulation::EnemyPopulation(int32 ID, int32 Type1, int32 Type2, int32 Type3)
{
	TypeID = ID;
	MinFloor = (ID - 1) * 5;
	Weight = 10 * ID;
	Classes.Add(MakeShared<EnemyClass>(Type1, ID, 1, 2 * (0.5 + 0.5 * ID), 10));
	Classes.Add(MakeShared<EnemyClass>(Type2, ID, 2, 3 * (0.5 + 0.5 * ID), 8));
	Classes.Add(MakeShared<EnemyClass>(Type3, ID, 3, 5 * (0.5 + 0.5 * ID), 5));
}
