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

UY_RoomWidget* UY_RoomWidget::CurrentRoom = nullptr;

void UY_RoomWidget::RoomInit()
{
	Y::GetLocation() = FVector(0, 0, 300);
	Y::GetRotation() = FRotator(0, 90, 0);
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
	Y::GetEnemys().Add((AY_Enemy*)Y::GetPlayer()->GetWorld()->SpawnActor(Y::GetGameInstance()->EnemyClasses.Find(TEXT("Enemy0"))->Get(), &EnemyVector,&ActorRotator));
	Y::GetEnemys()[0]->StandFloor = Y::GetFloors()[Enum];
	Y::GetFloors()[Enum]->StandCharacter = Y::GetEnemys()[0];

	for (int32 i = 0; i < 5; i++)
	{
		AY_Card::DrawCard(TEXT("Card0"));
	}
	AY_Card::DrawCard(TEXT("Card1"));
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
	for (int32 i = 0; i < 5; i++)
	{
		AY_Card::DrawCard(TEXT("Card0"));
	}
	AY_Card::DrawCard(TEXT("Card1"));
}
