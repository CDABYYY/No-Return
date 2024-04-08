// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Buff.h"
/**
 * 
 */
class DEMO0_API Y_StatusBar
{
public:
	Y_StatusBar();
	~Y_StatusBar();
	TArray<TSharedPtr<Y_Buff>> Buff;
	void AddBuffs(Y_StatusBar& OtherStatus);
	void AddBuff(TSharedPtr<Y_Buff> OtherBuff);
	void AddBuff(Y_Buff* OtherBuff);
	int32 RemoveBuff(int32 BuffID, int32 RemoveCount = 1024);
	int32 RemoveBuffLevel(int32 BuffLevel, int32 RemoveCount = 1024);
	int32 RemoveBuff(TSharedPtr<Y_Buff> RemovedBuff);
	template<class T>
	int32 RemoveBuff(T Condition,int32 RemoveCount = 1024);
	int32 FindCondition();
	TArray<TSharedPtr<Y_Buff>> FindBuff(int32 BuffNumber);
	int32 ExecuteBuffs(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false);
	int32 ExecuteBIA(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false);
};

template<class T>
inline int32 Y_StatusBar::RemoveBuff(T Condition,int32 RemoveCount)
{
	int32 AbandonBuff = 0;
	int32 i;
	for (i = 0; i < Buff.Num() && AbandonBuff < RemoveCount ;i++) {
		if (Condition(Buff[i])) {
			Buff[i]->RemoveFromCharacter();
			AbandonBuff++;
		}
		else {
			Buff[i - AbandonBuff] = Buff[i];
		}
	}
	for (i; i < Buff.Num(); i++) {
		Buff[i - AbandonBuff] = Buff[i];
	}
	int32 Removed = AbandonBuff;
	Buff.RemoveAt(Buff.Num() - AbandonBuff, AbandonBuff);
	return Removed;
}
