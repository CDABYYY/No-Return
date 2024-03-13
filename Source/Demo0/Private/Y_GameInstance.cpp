// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_GameInstance.h"
#include "Y_Ally.h"
#include "CameraPawn.h"
#include "Y_Card.h"
#include "Y_Floor.h"
#include "Y_TimeLine.h"
#include "Y.h"
#include "Y_Enemy.h"
#include "Y_RoomWidget.h"

UY_GameInstance* UY_GameInstance::YGI = nullptr;



UY_GameInstance::UY_GameInstance()
{
	RunTime = 0;
	YGI = this;
	Cards.SetNum(0);
	//For Debug StartMap
	Floors.SetNum(0);
	AtkOrder.SetNum(0);

	NowVector = FVector(0,0,300);
	NowRotator = FRotator(0,0,0);

	//RandomStream = FRandomStream(0);
	HaveRandoms = 0;
}


void UY_GameInstance::EndRoom()
{
	if (IsValid(Y::GetMainCharacter()))Y::GetMainCharacter()->Destroy();
	Y::GetMainCharacter() = nullptr;
	for (auto& p : Y::GetEnemys())if (IsValid(p))p->Destroy();
	Y::GetEnemys().Empty();
	for (auto& p : Y::GetCards())if (IsValid(p))p->Destroy();
	Y::GetCards().Empty();
	for (auto& p : Y::GetFloors())if (IsValid(p))p->Destroy();
	Y::GetFloors().Empty();
	if(IsValid(UY_RoomWidget::CurrentRoom))
		UY_RoomWidget::CurrentRoom->FightEnd();
	UY_RoomWidget::CurrentRoom = nullptr;
}

void UY_GameInstance::AddAtk(AY_Character* owner)
{
	if(IsValid(UY_TimeLine::YTimeLine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Call AddCharacterProfile"));
		//Correct On first Run. Will Crash on the next. Maybe the order of BeginPlay effect it.
		UY_TimeLine::YTimeLine->AddCharacterProfile(owner);
	}

	for (int32 i = 0; i < AtkOrder.Num(); i++) {
		if (owner->CharacterAttackTime<AtkOrder[i]->CharacterAttackTime ||
			owner->CharacterAttackTime == AtkOrder[i]->CharacterAttackTime &&
			owner->CharacterPriority> AtkOrder[i]->CharacterPriority) {
			AtkOrder.Insert(owner, i);
			return;
		}
	}
	AtkOrder.Add(owner);
}

void UY_GameInstance::HelpTick(float DeltaTime)
{
	RunTime += DeltaTime; 
	while (AtkOrder.Num() > 0) {
		if(!IsValid(AtkOrder[0]))
		{
			AtkOrder.RemoveAt(0);
			continue;
		}
		else {
			if (RunTime * 10 >= AtkOrder[0]->CharacterAttackTime) {
				AtkOrder[0]->Attack();
				AtkOrder.RemoveAt(0);
			}
			else break;
		}
	}
}

void UY_GameInstance::DeleteAtk(AY_Character* owner)
{
	AtkOrder.Remove(owner);
}


