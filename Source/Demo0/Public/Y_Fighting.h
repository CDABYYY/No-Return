// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YOArray.h"
#include "Y_StatusBar.h"
//#include "Y.h"

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
	TArray<TSharedPtr<class Y_Equipment>> Equipments;

	//This is for Event. Recommand to Delete it when end event.
	Y_StatusBar EventBuffs;
	Y_StatusBar AlwaysBuffs;
	Y_StatusBar FightingBuffs;

	Y_StatusBar OnCharacterBuffs;

	TSharedPtr<class Y_RoomInfo> CurrentRoom;
	
	//Using Execute Method
	void ExecuteToAllCharacter(TSharedPtr<class Y_Buff> ToExecuteBuff);

	void BeginRoom();
	void BeginFight();
	void AfterFight();
	void EndRoom();
	void SpawnCharacter(class AY_Character* SpawnedCharacter);
	void AddEquipment(TSharedPtr<class Y_Equipment> GetEquipment);
	void AddCard(TSharedPtr<class Y_CardInfo> GetCard);
	void RemoveEquipment(TSharedPtr<class Y_Equipment> GetEquipment);
	TArray<TSharedPtr<class Y_Equipment>> EquipmentUpgrades(int32 Level);
	void AddMoney(int32 Moneys);
	int32& MoneyCount();

	void DrawCard(TSharedPtr<class Y_CardInfo> ToDrawCard, bool VoidSpawn = false);
	void DrawCard(int32 DrawCount = 1);

	//LeaveType: 0:Played, 1:Discarded
	void UseCard(class AY_Card* UsedCard, int32 LeaveType = 0);
	//DiscardReason: 0:Played, 1:Discarded
	void UseCard(TSharedPtr<class Y_CardInfo> UsedCard, int32 DiscardReason = 0);

	void PrepareDie(class AY_Character* ToDieCharacter);
	void DestroyCharacter(class AY_Character* ToDestroyCharacter);


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
	TArray<TSharedPtr<class Y_EnemyInfo>> AppearedEnemys;

	TArray<TSharedPtr<class Y_RoomInfo>> ReadyRooms;
	TArray<TSharedPtr<class Y_Equipment>> ReadyEquipments;
	TArray<TSharedPtr<class Y_CardInfo>> ReadyCards;
	TArray<int32> CanSpawnCards;

	TSharedPtr<class Y_SettleInfo> SettleInfo;

	TSharedPtr<class Y_CardInfo> MCSkill;

	TSharedPtr<class Y_CardInfo> GetRandomCard();
	TSharedPtr<class Y_Equipment> GetRandomEquipment();

	int32 CurrentLevelNum;
	int32 CurrentFloor;
	TSharedPtr<class Y_LevelInfo> CurrentLevel;
	void LoadLevel(TSharedPtr<class Y_LevelInfo> ToLoadLevel);
	void ForwardLevel();

	int32 Money;
	int32 Health;
	int32 MaxHealth;
};


class DEMO0_API Y_LevelInfo {
public:
	class EnemyClass {
	public:
		virtual ~EnemyClass() {};
		int32 EnemyID;
		int32 Population;
		int32 Type;
		float CostLevel;
		float Weight;
		virtual float GetWeight();
		EnemyClass(int32 ThisEnemyID, int32 ThisPopulation, int32 ThisType, float ThisCostLevel, float ThisWeight);
	};
	class EnemyPopulation {
	public:
		virtual ~EnemyPopulation() {};
		TArray <TSharedPtr< EnemyClass >> Classes;
		float MinFloor;
		float Weight;
		int32 TypeID;
		virtual float GetWeight();
		EnemyPopulation();
		EnemyPopulation(int32 ID,int32 Type1,int32 Type2,int32 Type3);
	};
	Y_LevelInfo();
	virtual ~Y_LevelInfo();
	int32 LevelID;
	FString LevelName;
	TArray <TSharedPtr< EnemyPopulation >> ThisLevelPopulations;
	TArray<int32> ThisLevelRooms;
	TArray<int32> ThisLevelCards;
	TArray<int32> ThisLevelEquipments;
	TArray<int32> ThisLevelFloors;

	TSharedPtr<class Y_RoomInfo> FinalRoom;
	UTexture2D* MapTexture;

	FVector LevelLocation;
	FRotator LevelRotation;
	class USoundCue* LevelMusic;

	float GetWeight();
	//Use Bit To Mark If Can Use;
	int32 CanInLevel;
	float Weight;
	virtual void Loaded();

	virtual void UnLoad();
};
