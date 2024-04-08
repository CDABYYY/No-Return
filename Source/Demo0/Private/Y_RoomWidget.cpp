// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_RoomWidget.h"
#include "Y.h"
#include "CameraPawn.h"
#include "Y_Card.h"
#include "Y_GameInstance.h"
#include "Y_Character.h"
#include "Y_Floor.h"
#include "Y_Ally.h"
#include "Y_Enemy.h"
#include "Y_Buff.h"
#include "Y_EnemyInfo.h"
#include "Y_PlayerController.h"
#include "Y_Fighting.h"
#include "Y_MapWidget.h"

UY_RoomWidget* UY_RoomWidget::CurrentRoom = nullptr;



FText UY_RoomWidget::GetDescribe()
{
	return Info->GetDescribe();
}

void UY_RoomWidget::SetArrivable()
{
	Info->SetArrivable();
}

bool UY_RoomWidget::IsArrivable()
{
	return Info->IsArrivable();
}

void UY_RoomWidget::Passed()
{
	Info->Passed();
}

void UY_RoomWidget::RoomInit()
{
	Y::GetLocation() = FVector(0, 0, 300);
	Y::GetRotation() = FRotator(0, 90, 0);
	Info = MakeShared<Y_RoomInfo>();
}

void UY_RoomWidget::RoomClicked()
{
	Y::GetController()->MapWidget->PullMap(true);

	Y::GetGameInfo()->BeginFight();

	if (!Info.IsValid())
		Info = MakeShared<Y_RoomInfo>();
	
	auto TmpInfo = Info->RoomClicked();
	while (TmpInfo != nullptr) {
		Info = TmpInfo;
		TmpInfo = Info->RoomClicked();
	}
	

}

void UY_RoomWidget::RoomClosed()
{
	Info->LeaveRoom();
	Y::GetGameInfo()->AfterFight();
	Y::GetController()->MapWidget->ForwardRoom(this);
	Y::GetController()->MapWidget->PullMap(false);
}

void UY_RoomWidget::FightBegin()
{
	CurrentRoom = this;

	Y::GetPlayer()->SetActorLocation(FVector(0,0,190));
	Y::GetPlayer()->SetActorRotation(FRotator(0, 0, 0));
	Y::GetPlayer()->ClickAble = false;

	FRotator ActorRotator(0, 90, 0);

	for (int32 i = 0; i < 10; i++) {
		FVector FloorVector(130, -130 * 5 + i * 130, 64);
		Y::GetFloors().Add((AY_Floor*)Y::GetPlayer()->GetWorld()->SpawnActor(AY_Floor::StaticClass(), &FloorVector));
		Y::GetFloors()[i]->SerialNumber = i;
	}

	int MCnum = 2;
	FVector AllyVector = Y::GetFloors()[MCnum]->TargetLocation() + FVector(0, 0, 90);
	UY_GameInstance::YGI->MainCharacter = (AY_Ally*)Y::GetPlayer()->GetWorld()->SpawnActor(Y::GetGameInstance()->AllyClasses.Find(TEXT("Ally0"))->Get(), &AllyVector,&ActorRotator);
	Y::GetMainCharacter()->StandFloor = Y::GetFloors()[MCnum];
	Y::GetFloors()[MCnum]->StandCharacter = Y::GetMainCharacter();

	int Enum = 7;
	ActorRotator.Yaw = -90;
	FVector EnemyVector = Y::GetFloors()[Enum]->TargetLocation() + FVector(0, 0, 88);
	Y::GetEnemys().Add(Cast<AY_Enemy>(Y::GetPlayer()->GetWorld()->SpawnActor(Y::GetGameInstance()->EnemyClasses.Find(TEXT("Enemy0"))->Get(), &EnemyVector,&ActorRotator)));
	Y::GetEnemys()[0]->StandFloor = Y::GetFloors()[Enum];
	Y::GetFloors()[Enum]->StandCharacter = Y::GetEnemys()[0];

	Y::GetGameInfo()->DrawCard(5);
}

void UY_RoomWidget::EventBegin()
{
	CurrentRoom = this;

	Y::GetPlayer()->SetActorLocation(FVector(0, 0, 250));
	Y::GetPlayer()->SetActorRotation(FRotator(0, 0, 0));

	FRotator ActorRotator(0, 90, 0);

	for (int32 i = 0; i < 10; i++) {
		FVector FloorVector(130, -130 * 5 + i * 130, 64);
		Y::GetFloors().Add((AY_Floor*)Y::GetPlayer()->GetWorld()->SpawnActor(AY_Floor::StaticClass(), &FloorVector));
		Y::GetFloors()[i]->SerialNumber = i;
	}

	int MCnum = 2;
	FVector AllyVector = Y::GetFloors()[MCnum]->TargetLocation() + FVector(0, 0, 90);
	UY_GameInstance::YGI->MainCharacter = (AY_Ally*)Y::GetPlayer()->GetWorld()->SpawnActor(Y::GetGameInstance()->AllyClasses.Find(TEXT("Ally0"))->Get(), &AllyVector, &ActorRotator);
	Y::GetMainCharacter()->StandFloor = Y::GetFloors()[MCnum];
	Y::GetFloors()[MCnum]->StandCharacter = Y::GetMainCharacter();

	int Enum = 7;
	FVector EnemyVector = Y::GetFloors()[Enum]->TargetLocation() + FVector(0, 0, 88);
	Y::GetEnemys().Add((AY_Enemy*)Y::GetPlayer()->GetWorld()->SpawnActor(Y::GetGameInstance()->EnemyClasses.Find(TEXT("Enemy0"))->Get(), &EnemyVector, &ActorRotator));
	Y::GetEnemys()[0]->StandFloor = Y::GetFloors()[Enum];
	Y::GetFloors()[Enum]->StandCharacter = Y::GetEnemys()[0];
}

void UY_RoomWidget::FightEnd()
{
	//CurrentRoom = nullptr;
}

void UY_RoomWidget::EventEnd()
{
}

void UY_RoomWidget::EventFight()
{
	Y::GetPlayer()->SetActorLocation(FVector(0, 0, 190));
	//for (int32 i = 0; i < 5; i++)
	//{
	//	AY_Card::DrawCard(TEXT("Card0"));
	//}
	//AY_Card::DrawCard(TEXT("Card1"));
}

FText Y_RoomInfo::GetDescribe()
{
	return FText::FromString(TEXT("Unknown"));
}

void Y_RoomInfo::SetArrivable()
{
	Arriveable = true;
}

bool Y_RoomInfo::IsArrivable()
{
	return Arriveable;
}

void Y_RoomInfo::Passed()
{
	Arriveable = false;
}

TSharedPtr<Y_RoomInfo> Y_RoomInfo::RoomClicked()
{
	//return Y::getRandom(Y::GetGameInfo()->ReadyRooms);

	Y::GetPlayer()->SetActorLocation(FVector(0, 0, 190));
	Y::GetPlayer()->SetActorRotation(FRotator(0, 0, 0));
	Y::GetPlayer()->ClickAble = false;

	FRotator ActorRotator(0, 90, 0);

	for (int32 i = 0; i < 10; i++) {
		Y::GetGameInfo()->SpawnFloor(Y::FloorInfos().Find(0)->Get()->NewObject(), i);
	}

	Y::GetGameInfo()->SpawnMC(Y::GetFloors()[2]);

	auto TC = Y::GetGameInfo()->SpawnCharacter(Y::CharacterInfos().Find(0)->Get()->NewObject(), Y::GetFloors()[7]);
	TC->Buffs->AddBuff(MakeShared<Y_BuffR>(this));

	Y::GetGameInfo()->DrawCard(5);
	return nullptr;


}

void Y_RoomInfo::LeaveRoom()
{
}

float Y_RoomInfo::GetWeight()
{
	return 10;
}
