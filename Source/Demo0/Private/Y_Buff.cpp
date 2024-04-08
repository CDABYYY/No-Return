// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Buff.h"
#include "CoreMinimal.h"
#include "Y_StatusBar.h"
#include "Y_Character.h"
#include "Y_RoomWidget.h"

Y_Buff::Y_Buff()
{
	TriggerCondition = Injuring | DetectDeath;
	BuffCount = 0;
	BuffNumber = 1;
	BuffOrder = 1000;
	BuffLevel = 0;
}

void Y_Buff::Init(int32 BuffCount0)
{
	this->BuffCount = BuffCount0;
}

Y_Buff::~Y_Buff()
{
}


int32 Y_Buff::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	if (ExecuteCondition & Injuring){
		ToCharacter->Health -= BuffCount;
		return 0;
	}
	if (ExecuteCondition & DetectDeath) {
		if (ToCharacter->Health <= 0)
		{
			return BuffNumber;
		}
		else return 0;
	}
	return 0;
}

FText Y_Buff::printBuff(bool PrintLog) const
{
	if(PrintLog)
		return FText::FromString(TEXT("Description of Health"));

	return FText::FromString(FString::Printf(TEXT("Health: %d"), BuffCount));
}

void Y_Buff::AddBuff(Y_Buff* OtherBuff)
{
	BuffCount += OtherBuff->BuffCount;
}

void Y_Buff::AddToCharacter(AY_Character* TargetCharacter)
{
	TargetCharacter->Buffs->AddBuff(AsShared());
	OwnerCharacter = TargetCharacter;
}

void Y_Buff::RemoveFromCharacter()
{
}

bool Y_Buff::AcceptBuffAdd(Y_Buff* OtherBuff)
{
	return Addable && OtherBuff->Addable;
}

void Y_Buff::AddInExecuteLog()
{
	//FBuffLog::WritingLog.ExecuteBuffs.Add(this->AsShared());
}

void Y_Buff::AddInInfluentLog()
{
	//FBuffLog::WritingLog.InfluentBuffs.Add(this->AsShared());
}

//TArray<FBuffLog> FBuffLog::FightLogs = TArray<FBuffLog>();
//FBuffLog FBuffLog::WritingLog = FBuffLog();

Y_BuffR::Y_BuffR(class Y_RoomInfo* BindWidget)
{
	BindedWidget = BindWidget;
	BindedWidget->NeedKills += 1;
	TriggerCondition = AfterDeath;
	BuffOrder = 1000;
	BuffCount = 1;
	BuffNumber = 10001;
}

int32 Y_BuffR::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	BindedWidget->NeedKills -= 1;
	if (BindedWidget->NeedKills <= 0) {
		BindedWidget->Owner->RoomClosed();
	}
	return 0;
}

int32 Y_BuffL::execute(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack)
{
	return ToExecute.Execute(); 
}
