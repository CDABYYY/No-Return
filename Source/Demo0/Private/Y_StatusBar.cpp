// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_StatusBar.h"
#include "CoreMinimal.h"

Y_StatusBar::Y_StatusBar()
{
}

Y_StatusBar::~Y_StatusBar()
{
}

void Y_StatusBar::AddBuffs(Y_StatusBar& OtherStatus)
{
	for (auto& p : OtherStatus.Buff) {
		AddBuff(p);
	}
}

void Y_StatusBar::AddBuff(TSharedPtr<Y_Buff> OtherBuff)
{
	int32 InsertPosition = 0;
	for (; InsertPosition < Buff.Num(); InsertPosition++) {
		if (OtherBuff->BuffOrder > Buff[InsertPosition]->BuffOrder) break;
		if (OtherBuff->BuffNumber == Buff[InsertPosition]->BuffNumber
			&& Buff[InsertPosition]->AcceptBuffAdd(OtherBuff.Get()))
			Buff[InsertPosition]->AddBuff(OtherBuff.Get());
	}
	if (InsertPosition == Buff.Num())Buff.Add(OtherBuff);
	else Buff.Insert(OtherBuff, InsertPosition);
}

void Y_StatusBar::AddBuff(Y_Buff* OtherBuff)
{
	AddBuff(TSharedPtr<Y_Buff>(OtherBuff));
}

int32 Y_StatusBar::FindCondition()
{
	int32 FindedCondition = 0;
	for (auto& p : Buff) {
		if (p->TriggerCondition & Y_Buff::Injuring) {
			FindedCondition = Y_Buff::Injuring;
			break;
		}
		if (p->TriggerCondition & Y_Buff::Moving) {
			FindedCondition = Y_Buff::Moving;
			break;
		}
		if (p->TriggerCondition & Y_Buff::Buffing) {
			FindedCondition = Y_Buff::Buffing;
			break;
		}
	}
	return FindedCondition;
}

TArray<TSharedPtr<Y_Buff>> Y_StatusBar::FindBuff(int32 BuffNumber)
{
	TArray<TSharedPtr<Y_Buff>> TmpArray;
	for (auto& p : Buff) {
		if (p->BuffNumber == BuffNumber)TmpArray.Add(p);
	}
	return TmpArray;
}

int32 Y_StatusBar::ExecuteBuffs(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	int ExecuteStatus = 0;
	for (auto& p : Buff) {
		if (p->TriggerCondition & ExecuteCondition)
			ExecuteStatus = p->execute(FromCharacter, ToCharacter, ToBuffs, ExecuteCondition,TriggerAction, TryAttack);
		if (ExecuteStatus != 0) break;
	}
	return ExecuteStatus;
}

