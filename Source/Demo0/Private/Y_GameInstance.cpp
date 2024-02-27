// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_GameInstance.h"
#include "Y_Character.h"
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
	if (AtkOrder.Num() > 0 && AtkOrder[0] != nullptr && RunTime >= AtkOrder[0]->CharacterAttackTime) {
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ATK Play"));
		AtkOrder.RemoveAt(0);
	}
		
}

void UY_GameInstance::DeleteAtk(AY_Character* owner)
{
	AtkOrder.Remove(owner);
}


