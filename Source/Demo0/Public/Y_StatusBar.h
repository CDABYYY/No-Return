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
	int32 FindCondition();
	TArray<TSharedPtr<Y_Buff>> FindBuff(int32 BuffNumber);
	int32 ExecuteBuffs(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false);
};
