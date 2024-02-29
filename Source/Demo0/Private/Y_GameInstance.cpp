// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_GameInstance.h"
#include "Y_Ally.h"
#include "CameraPawn.h"
#include "Y_Card.h"
#include "Y_Floor.h"

UY_GameInstance* UY_GameInstance::YGI = nullptr;



UY_GameInstance::UY_GameInstance()
{
	RunTime = 0;
	YGI = this;
	Cards.SetNum(10);
	Floors.SetNum(20);
	AtkOrder.SetNum(0);
	for (auto& p : Cards)p = nullptr;
	for (auto& p : Floors)p = nullptr;
}

void UY_GameInstance::AddAtk(AY_Character* owner)
{
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


