// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DEMO0_API Y_Buff
{
public:
	Y_Buff();
	virtual ~Y_Buff();
	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString BuffName;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ConnectAble;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuffLevel;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuffCount;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuffNumber;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuffOrder;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AY_Character* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuffProperty;

	FString CountName;
	int32 TriggerCondition;
	bool Addable;
	bool Living;

	enum : int32
	{
		//Begin Action
		BeginAction = (1 << 1),
		//Begin Attack
		BeginAttack = (1 << 2),
		//Begin Injured
		BeginInjured = (1 << 3),
		//Injuring
		Injuring = (1 << 4),
		//After Injured
		AfterInjured = (1 << 5),
		//After Attack
		AfterAttack = (1 << 6),
		//Begin Move
		BeginMove = (1 << 7),
		//Begin Moved
		BeginMoved = (1 << 8),
		//Moving
		Moving = (1 << 9),
		//After Moved
		AfterMoved = (1 << 10),
		//After Move
		AfterMove = (1 << 11),
		//Begin Buff
		BeginBuff = (1 << 12),
		//Begin Buffed
		BeginBuffed = (1 << 13),
		//Buffing
		Buffing = (1 << 14),
		//After Buffed
		AfterBuffed = (1 << 15),
		//After Buff
		AfterBuff = (1 << 16),
		//After Action
		AfterAction = (1 << 17),
		//Death Detect
		DetectDeath = (1 << 18),
		//Begin Death
		BeginDeath = (1 << 19),
		//After Death
		AfterDeath = (1 << 20),
		//Begin Tick
		BeginTick = (1 << 21),
		//Ticking
		Ticking = (1 << 22),
		//After Tick
		AfterTick = (1 << 23),
		//Kill Event
		AfterKill = (1 << 24),
		//Reversed Events , The first Buff of ToBuff will show its Type 
		ReversedEvent = (1 << 25),
	};

	//Return Without 0 will end Following Execute				
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs,int32 ExecuteCondition,FString TriggerAction, bool TryAttack = false);
	virtual FString printBuff(bool PrintLog = false)const;
	virtual void AddBuff(Y_Buff* OtherBuff);
	virtual void AddToCharacter(class AY_Character* TargetCharacter);
	virtual void RemoveFromCharacter(class AY_Character* TargetCharacter);
	virtual bool AcceptBuffAdd(Y_Buff* OtherBuff);
};
