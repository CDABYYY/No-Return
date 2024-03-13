// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Buff.h"
#include "CoreMinimal.h"
#include "Y_StatusBar.h"
#include "Y_Character.h"

Y_Buff::Y_Buff()
{
	TriggerCondition = Injuring | DetectDeath;
	BuffCount = 0;
	BuffNumber = 1;
	BuffOrder = 1000;
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

FString Y_Buff::printBuff(bool PrintLog) const
{
	if(PrintLog)
		return FString(TEXT("Description of Health"));

	return FString::Printf(TEXT("Health: %d"), BuffCount);
}

void Y_Buff::AddBuff(Y_Buff* OtherBuff)
{
	BuffCount += OtherBuff->BuffCount;
}

void Y_Buff::AddToCharacter(AY_Character* TargetCharacter)
{
}

void Y_Buff::RemoveFromCharacter(AY_Character* TargetCharacter)
{
}

bool Y_Buff::AcceptBuffAdd(Y_Buff* OtherBuff)
{
	return Addable && OtherBuff->Addable;
}
