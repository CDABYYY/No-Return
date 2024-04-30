// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Buff.h"
#include "CoreMinimal.h"
#include "Y_StatusBar.h"
#include "Y_Character.h"
#include "Y_RoomWidget.h"
#include "Y_BuffIcon.h"
#include "Y_CardInfo.h"
#include "Y_EnemyInfo.h"

Y_Buff::Y_Buff()
{
	TriggerCondition = Buffing;
	BuffProperty = 0;
	BuffCount = 1;
	BuffAsType = BuffID = 0;
	BuffOrder = 0;
	BuffLevel = 0;
	Addable = true;
	Living = true;
	OwnerCharacter = nullptr;
	ShowAble = true;
	IconWidget = nullptr;
	BuffDescribe = Y::PrintText(TEXT("Buff Describe"));
	//FString SP = TEXT("/Script/Engine.Texture2D'/Game/Resource/Png/JayceThunderingBlow.JayceThunderingBlow'");
	//BuffPicture = Y::LoadPicture(SP);
}

void Y_Buff::Init(int32 BuffCount0)
{
	this->BuffCount = BuffCount0;
}

Y_Buff::~Y_Buff()
{
}

FText Y_Buff::GetDescribe()
{
	return BuffDescribe;
}

UTexture2D* Y_Buff::GetPicture()
{
	return BuffPicture;
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
			return BuffID;
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
	if (BuffCount == 0)
	{
		RemoveFromCharacter();
	}
	if (Living == false) {
		Living = true;
	}
}

void Y_Buff::ReplaceBuff(Y_Buff* OtherBuff)
{
	BuffCount = OtherBuff->BuffCount;
	IconWidget = OtherBuff->IconWidget;
	IconWidget->Buff = AsShared();
}

void Y_Buff::AddToCharacter(AY_Character* TargetCharacter, bool Execute)
{
	OwnerCharacter = TargetCharacter;
	TargetCharacter->AddBuff(AsShared(), Execute);
}

void Y_Buff::RemoveFromCharacter()
{
	Living = false;
	//OwnerCharacter->Buffs->RemoveBuff(AsShared());
}

bool Y_Buff::AcceptBuffAdd(Y_Buff* OtherBuff)
{
	return Addable && OtherBuff->Addable;
}

FString Y_Buff::PrinCount()
{
	FString TmpString = BuffName.ToString();
	return FString::Printf(TEXT("%d层%s"), BuffCount, *(TmpString));
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
	BuffID = 10001;
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

CardBuff::CardBuff(TSharedPtr<class Y_CardInfo> Card)
{
	BuffID = 10000 + Card->CardID;
	BuffCount = Card->OriginalCost;
	BuffExtend = Card->CardTypes;
	CardInfo = Card;
}

void CardBuff::AddToCharacter(AY_Character* TargetCharacter,bool Execute)
{

}

ActionBuff::ActionBuff(TSharedPtr<class Y_CharacterAction> Action)
{
	BuffID = 20000 + Action->ActionID;
	BuffCount = Action->OriginalCost;
	ActionInfo = Action;
}

void ActionBuff::AddToCharacter(AY_Character* TargetCharacter,bool Execute)
{

}
