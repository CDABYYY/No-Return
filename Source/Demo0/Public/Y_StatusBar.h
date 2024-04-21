// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Buff.h"
#include "Y.h"
/**
 * 
 */
class DEMO0_API Y_StatusBar
{
public:
	Y_StatusBar();
	Y_StatusBar(std::initializer_list <TSharedPtr< Y_Buff >> BuffList);
	~Y_StatusBar();
	TArray<TSharedPtr<Y_Buff>> Buff;
	void AddBuffs(Y_StatusBar& OtherStatus);
	void AddBuff(TSharedPtr<Y_Buff> OtherBuff,int32 Merge = 0);
	void AddBuff(Y_Buff* OtherBuff,int32 Merge = 0);
	int32 RemoveBuff(int32 BuffID, int32 RemoveCount = 1024);
	int32 RemoveBuffLevel(int32 BuffLevel, int32 RemoveCount = 1024);
	int32 RemoveBuff(TSharedPtr<Y_Buff> RemovedBuff);
	template<class T>
	int32 RemoveBuff(T Condition,int32 RemoveCount = 1024);
	int32 FindCondition();
	TArray<TSharedPtr<Y_Buff>> FindBuff(int32 BuffNumber);
	TArray<TSharedPtr<Y_Buff>> FindType(int32 BuffType);
	TArray<TSharedPtr<Y_Buff>> FindBuffExtend(int32 BuffID);
	template<class T>
	int32 ReplaceBuff(int32 BuffType, int32 RemoveCount = 1024);
	int32 ExecuteBuffs(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false);
	int32 ExecuteBIA(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false);
};

template<class T>
inline int32 Y_StatusBar::RemoveBuff(T Condition,int32 RemoveCount)
{
	int32 AbandonBuff = 0;
	//TArray<TSharedPtr<Y_Buff>> TmpBuffs = TArray<TSharedPtr<Y_Buff>>(Buff);
	for (auto& p : Buff) {
		if (Condition(p)) {
			if (AbandonBuff >= RemoveCount)break;
			p->RemoveFromCharacter();
			AbandonBuff++;
		}
	}
	return AbandonBuff;
}

template<class T>
inline int32 Y_StatusBar::ReplaceBuff(int32 BuffType, int32 RemoveCount)
{
	int Replaced = 0;
	for (int32 i = 0; i < Buff.Num();i++) {
		if (Buff[i]->BuffAsType == BuffType) {
			TSharedPtr<Y_Buff> pt = Y::YMakeShared<T>();
			pt->ReplaceBuff(Buff[i].Get());
			Buff[i] = pt;
			Replaced++;
		}
	}
	return Replaced;
}
