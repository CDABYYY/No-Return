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
#include "Y.h"

Y_Fighting::Y_Fighting()
{
	Equipments.reset([](TSharedPtr<Y_Equipment>& a, TSharedPtr<Y_Equipment>& b) 
		{return a->EquipmentPriority < b->EquipmentPriority; });

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
	ToExecuteBuffs.AddBuff(ToExecuteBuff);
}

void Y_Fighting::BeginFight()
{
	EventBuffs.ExecuteBuffs(nullptr, nullptr, EventBuffs, Y_Buff::BeginFight, TEXT("Begin Fight"));
	EquipmentBuffs.ExecuteBuffs(nullptr, nullptr, EquipmentBuffs, Y_Buff::BeginFight, TEXT("Begin Fight"));
	//ToExecuteBuffs.ExecuteBuffs(nullptr, nullptr, ToExecuteBuffs, Y_Buff::BeginFight, TEXT("Begin Fight"));
	SettleInfo = MakeShared<Y_SettleInfo>();

	for (auto& p : UsingCards) {
		ToDrawCards.Add(p);
	}
	Y::GetGameInstance()->RunTime = 0;
	Y::GetGameInstance()->TickTime = 20;
	Y::GetPlayer()->ClickAble = false;
}

void Y_Fighting::AfterFight()
{
	ToExecuteBuffs.ExecuteBuffs(nullptr, nullptr, ToExecuteBuffs, Y_Buff::AfterFight, TEXT("After Fight"));
	EquipmentBuffs.ExecuteBuffs(nullptr, nullptr, EquipmentBuffs, Y_Buff::AfterFight, TEXT("After Fight"));
	EventBuffs.ExecuteBuffs(nullptr, nullptr, EventBuffs, Y_Buff::AfterFight, TEXT("After Fight"));
	ToExecuteBuffs = Y_StatusBar();

	if (IsValid(Y::GetMainCharacter()))Y::GetMainCharacter()->Destroy();
	Y::GetMainCharacter() = nullptr;
	for (auto& p : Y::GetEnemys())if (IsValid(p))p->Destroy();
	Y::GetEnemys().Empty();
	for (auto& p : Y::GetCards())if (IsValid(p))p->Destroy();
	Y::GetCards().Empty();
	for (auto& p : Y::GetFloors())if (IsValid(p))p->Destroy();
	Y::GetFloors().Empty();

	UY_TimeLine::YTimeLine->EndRoom();
	
	ToDrawCards.Empty();
	DiscardedCards.Empty();
	InHandCards.Empty();
	ExhaustCards.Empty();

	Y::GetPlayer()->ClickAble = true;
}

void Y_Fighting::SpawnCharacter(AY_Character* SpawnedCharacter)
{
	EventBuffs.ExecuteBuffs(nullptr, SpawnedCharacter, EventBuffs, Y_Buff::CharacterSpawn, TEXT("Character Spawn"));
	EquipmentBuffs.ExecuteBuffs(nullptr, SpawnedCharacter, EquipmentBuffs, Y_Buff::CharacterSpawn, TEXT("Character Spawn"));
	ToExecuteBuffs.ExecuteBuffs(nullptr, SpawnedCharacter, ToExecuteBuffs, Y_Buff::CharacterSpawn, TEXT("Character Spawn"));
}

void Y_Fighting::AddEquipment(TSharedPtr<Y_Equipment> GetEquipment)
{
	Equipments.Add(GetEquipment);
	GetEquipment->Equiped();
}

void Y_Fighting::DrawCard(TSharedPtr<class Y_CardInfo> ToDrawCard, bool VoidSpawn)
{
	if (ToDrawCard == nullptr) {
		ToDrawCard = Y::getRandom(ToDrawCards);
	}
	ToDrawCards.Remove(ToDrawCard);
	ToDrawCard->Drawed();
	SpawnCard(ToDrawCard);
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

AY_Floor* Y_Fighting::SpawnFloor(TSharedPtr<class Y_FloorInfo> ToSpawnFloor, int32 SerialNumber, FName ActorClass)
{
	FVector ToVector(Y::GetLocation());
	FRotator ToRotator(Y::GetRotation());
	ToRotator += FRotator(0, 90, 0);
	FVector RelativeVector(130, SerialNumber * 130, 64);
	//RelativeVector = RelativeVector * ToRotator.Vector();
	FVector SpawnVector = Y::GetLocation() + RelativeVector;
	AY_Floor* NewFloor = Cast<AY_Floor>(Y::GetWorld()->SpawnActor(Y::GetGameInstance()->FloorClasses.Find(ActorClass)->Get(), &SpawnVector, &ToRotator));
	NewFloor->SerialNumber = SerialNumber;
	for (int32 i = Y::GetFloors().Num(); i <= SerialNumber; i++) {
		Y::GetFloors().Add(nullptr);
	}
	Y::GetFloors()[SerialNumber] = NewFloor;
	NewFloor->Info = ToSpawnFloor;
	ToSpawnFloor->Owner = NewFloor;
	return NewFloor;
}

AY_Card* Y_Fighting::SpawnCard(TSharedPtr<class Y_CardInfo> ToSpawnCard, FName ActorClass)
{
	FVector AF = Y::GetPlayer()->MyCamera->GetComponentLocation();
	AF += FVector(270, -208 + 52 * 15, -90);//Base Location
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
	FRotator ToRotator(Y::GetRotation());
	if (FromFloor->SerialNumber < Y::GetMainCharacter()->StandFloor->SerialNumber)
		ToRotator += FRotator(0, 90, 0);
	else 
		ToRotator += FRotator(0, -90, 0);
	FVector SpawnVector = FromFloor->TargetLocation();
	AY_Character* NewCharacter = Cast<AY_Character>(Y::GetWorld()->SpawnActor(Y::GetGameInstance()->EnemyClasses.Find(ActorClass)->Get(), &SpawnVector, &ToRotator));
	NewCharacter->StandFloor = FromFloor;
	FromFloor->StandCharacter = NewCharacter;
	NewCharacter->Info = ToSpawnCharacter;
	ToSpawnCharacter->Owner = NewCharacter;
	if (FromFloor->SerialNumber > Y::GetMainCharacter()->StandFloor->SerialNumber)
	{
		NewCharacter->Facing = -1;
		NewCharacter->Rotating = -90;
	}
	Y::GetEnemys().Add(NewCharacter);
	LivingEnemys.Add(ToSpawnCharacter);
	SpawnCharacter(NewCharacter);
	return NewCharacter;
}

AY_Character* Y_Fighting::SpawnMC(AY_Floor* FromFloor, FName ActorClass)
{
	FRotator ToRotator(Y::GetRotation());
	ToRotator += FRotator(0, 90, 0);
	FVector SpawnVector = FromFloor->TargetLocation();
	AY_Character* NewCharacter = Cast<AY_Character>(Y::GetWorld()->SpawnActor(Y::GetGameInstance()->AllyClasses.Find(ActorClass)->Get(), &SpawnVector, &ToRotator));
	NewCharacter->StandFloor = FromFloor;
	FromFloor->StandCharacter = NewCharacter;
	Y::GetMainCharacter() = NewCharacter;
	SpawnCharacter(NewCharacter);
	return NewCharacter;
}

