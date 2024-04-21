// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_StatusBar.h"
#include "CoreMinimal.h"

Y_StatusBar::Y_StatusBar()
{
}

Y_StatusBar::Y_StatusBar(std::initializer_list <TSharedPtr< Y_Buff >> BuffList)
{
	for (auto& B : BuffList)
	{
		AddBuff(B);
	}
}

Y_StatusBar::~Y_StatusBar()
{
}

void Y_StatusBar::AddBuffs(Y_StatusBar& OtherStatus)
{
	for (auto& p : OtherStatus.Buff) {
		AddBuff(p,1);
	}
}

void Y_StatusBar::AddBuff(TSharedPtr<Y_Buff> OtherBuff,int32 Type)
{
	int32 InsertPosition = 0;
	for (; InsertPosition < Buff.Num(); InsertPosition++) {
		if (OtherBuff->BuffOrder > Buff[InsertPosition]->BuffOrder) break;
		if (OtherBuff->BuffID == Buff[InsertPosition]->BuffID && Type != 0
			 && Buff[InsertPosition]->AcceptBuffAdd(OtherBuff.Get()))
		{
			Buff[InsertPosition]->AddBuff(OtherBuff.Get());
			return;
		}
	}
	if (InsertPosition == Buff.Num())Buff.Add(OtherBuff);
	else Buff.Insert(OtherBuff, InsertPosition);
}

void Y_StatusBar::AddBuff(Y_Buff* OtherBuff,int32 Type)
{
	AddBuff(MakeShareable(OtherBuff),Type);
}

int32 Y_StatusBar::RemoveBuff(int32 BuffID, int32 RemoveCount)
{
	return RemoveBuff([BuffID](TSharedPtr<Y_Buff>& buff) {return buff->BuffID == BuffID; }, RemoveCount);
}

int32 Y_StatusBar::RemoveBuffLevel(int32 BuffLevel, int32 RemoveCount)
{
	if (BuffLevel < 0)
		return RemoveBuff([BuffLevel](TSharedPtr<Y_Buff>& buff) {return buff->BuffLevel < 0 && buff->BuffLevel > BuffLevel; }, RemoveCount);
	if (BuffLevel > 0)
		return RemoveBuff([BuffLevel](TSharedPtr<Y_Buff>& buff) {return buff->BuffLevel > 0 && buff->BuffLevel < BuffLevel; }, RemoveCount);
	return 0;
}

int32 Y_StatusBar::RemoveBuff(TSharedPtr<Y_Buff> RemovedBuff)
{
	return Buff.Remove(RemovedBuff);
}

int32 Y_StatusBar::FindCondition()
{
	int32 FindedCondition = Y_Buff::Buffing;
/*	for (auto& p : Buff) {
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
*/
	for (auto& p : Buff) {
		if (p->BuffProperty == 1) {
			FindedCondition = Y_Buff::Injuring; break;
		}
		if (p->BuffProperty == 2) {
			FindedCondition = Y_Buff::Moving; break;
		}
		if (p->BuffProperty == 3) {
			FindedCondition = Y_Buff::Buffing; break;
		}
	}
	return FindedCondition;
}

TArray<TSharedPtr<Y_Buff>> Y_StatusBar::FindBuff(int32 BuffNumber)
{
	TArray<TSharedPtr<Y_Buff>> TmpArray;
	for (auto& p : Buff) {
		if (p->BuffID == BuffNumber)TmpArray.Add(p);
	}
	return TmpArray;
}

TArray<TSharedPtr<Y_Buff>> Y_StatusBar::FindType(int32 BuffType)
{
	TArray<TSharedPtr<Y_Buff>> TmpArray;
	for (auto& p : Buff) {
		if (p->BuffAsType == BuffType)TmpArray.Add(p);
	}
	return TmpArray;
}

TArray<TSharedPtr<Y_Buff>> Y_StatusBar::FindBuffExtend(int32 BuffID)
{
	TArray<TSharedPtr<Y_Buff>> TmpArray;
	for (auto& p : Buff) {
		if (p->BuffExtend.Contains(BuffID))
		{
			TmpArray.Add(p);
		}
	}
	return TmpArray;
}

int32 Y_StatusBar::ExecuteBuffs(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	int ExecuteStatus = 0;
	for (auto& p : Buff) {
		if (p->TriggerCondition & ExecuteCondition && p->Living)
			ExecuteStatus = p->execute(FromCharacter, ToCharacter, ToBuffs, ExecuteCondition,TriggerAction, TryAttack);
		if (ExecuteStatus != 0) break;
	}
	return ExecuteStatus;
}

int32 Y_StatusBar::ExecuteBIA(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	int32 ExecuteStatus = ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, ExecuteCondition >> 1, TriggerAction, TryAttack);
	if (ExecuteStatus == 0) {
		ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, ExecuteCondition, TriggerAction, TryAttack);
		ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, ExecuteCondition << 1, TriggerAction, TryAttack);
	}
	return ExecuteStatus;
}

