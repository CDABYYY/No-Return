// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YOArray.h"
#include "Y_StatusBar.h"

/**
 * 
 */
class DEMO0_API Y_Fighting
{
public:
	Y_Fighting();
	~Y_Fighting();
	
	//Equipments And Buffs Will Only Run On BeginFight, AfterFight, CharacterSpawn
	//If you want to Add Trigger To Other Times, Put it On Character when CharacterSpawn so it will run
	YOArray<TSharedPtr<class Y_Equipment>> Equipments;

	//This is for Event. Recommand to Delete it when end event.
	Y_StatusBar EventBuffs;
	Y_StatusBar EquipmentBuffs;
	Y_StatusBar ToExecuteBuffs;
	
	//Using Execute Method
	void ExecuteToAllCharacter(TSharedPtr<class Y_Buff> ToExecuteBuff);

	void BeginFight();
	void AfterFight();
	void SpawnCharacter(class AY_Character* SpawnedCharacter);
	void AddEquipment(TSharedPtr<class Y_Equipment> GetEquipment);

	void DrawCard(TSharedPtr<class Y_CardInfo> ToDrawCard, bool VoidSpawn = false);
	void DrawCard(int32 DrawCount = 1);

	//LeaveType: 0:Played, 1:Discarded
	void UseCard(class AY_Card* UsedCard, int32 LeaveType = 0);
	//DiscardReason: 0:Played, 1:Discarded
	void UseCard(TSharedPtr<class Y_CardInfo> UsedCard, int32 DiscardReason = 0);

	class AY_Floor* SpawnFloor(TSharedPtr<class Y_FloorInfo> ToSpawnFloor,int32 SerialNumber,FName ActorClass = TEXT("Default"));
	class AY_Card* SpawnCard(TSharedPtr<class Y_CardInfo> ToSpawnCard, FName ActorClass = TEXT("Default"));
	class AY_Character* SpawnCharacter(TSharedPtr<class Y_EnemyInfo> ToSpawnCharacter,class AY_Floor* FromFloor, FName ActorClass = TEXT("Default"));
	class AY_Character* SpawnMC(class AY_Floor* FromFloor, FName ActorClass = TEXT("Default"));

	TArray<TSharedPtr<class Y_CardInfo>> UsingCards;

	TArray<TSharedPtr<class Y_CardInfo>> ToDrawCards;
	TArray<TSharedPtr<class Y_CardInfo>> InHandCards;
	TArray<TSharedPtr<class Y_CardInfo>> DiscardedCards;
	TArray<TSharedPtr<class Y_CardInfo>> ExhaustCards;

	TArray<TSharedPtr<class Y_EnemyInfo>> LivingEnemys;
	TArray<TSharedPtr<class Y_RoomInfo>> ReadyRooms;

	TSharedPtr<class Y_SettleInfo> SettleInfo;

	TSharedPtr<class Y_CardInfo> MCSkill;
};
