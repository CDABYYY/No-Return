// Fill out your copyright notice in the Description page of Project Settings.


#include "Y.h"
#include "Y_GameInstance.h"
#include "Y_StatusBar.h"
#include "Y_Character.h"
#include "CameraPawn.h"
#include "Y_Equipment.h"
#include "Y_CardH.h"
#include "Y_CardW.h"
#include "Y_EquipmentH.h"
#include "Y_EquipmentW.h"
#include "Y_PlayerController.h"
#include "Y_Fighting.h"
#include "Y_HUD.h"

Y::Y()
{
}

Y::~Y()
{
}

TMap<int32, TSharedPtr<Y::Y_SubClassIF<class Y_CardInfo>>> Y::CardClass;
TMap<int32, TSharedPtr<Y::Y_SubClassIF<class Y_EnemyInfo>>> Y::CharacterClass;
TMap<int32, TSharedPtr<Y::Y_SubClassIF<class Y_Buff>>> Y::BuffClass;
TMap<int32, TSharedPtr<Y::Y_SubClassIF<class Y_RoomInfo>>> Y::RoomClass;
TMap<int32, TSharedPtr<Y::Y_SubClassIF<class Y_FloorInfo>>> Y::FloorClass;
TMap<int32, TSharedPtr<Y::Y_SubClassIF<class Y_Equipment>>> Y::EquipmentClass;

UY_GameInstance*& Y::GetGameInstance()
{
	return UY_GameInstance::YGI;
}

ACameraPawn*& Y::GetPlayer()
{
	return UY_GameInstance::YGI->YC;
}

TArray<class AY_Card*>& Y::GetCards()
{
	return UY_GameInstance::YGI->Cards;
}

TArray<class AY_Floor*>& Y::GetFloors()
{
	return UY_GameInstance::YGI->Floors;
}

TArray<class AY_Character*>& Y::GetEnemys()
{
	return UY_GameInstance::YGI->Enemys;
}

TSharedPtr<class Y_CardInfo> Y::GetChoosingCard()
{
	if(IsValid(GetController()->CardWidget->ChoosedCard))
	return GetController()->CardWidget->ChoosedCard->CardInfo;
	return nullptr;
}

float& Y::GetRunTime()
{
	return GetGameInstance()->RunTime;
}

TSharedPtr<class Y_Equipment> Y::GetChoosingEquipment()
{
	if(IsValid(GetController()->PCHUD->EquipmentWidget->ChoosedEquipment))
	return GetController()->PCHUD->EquipmentWidget->ChoosedEquipment->Info;
	return nullptr;
}

bool& Y::IsPressingEquipment()
{
	return GetController()->PCHUD->EquipmentWidget->Pressing;
}

bool& Y::IsPressingCard()
{
	return GetController()->CardWidget->Pressing;
}

FVector& Y::GetLocation()
{
	//return UY_GameInstance::YGI->NowVector;
	return GetGameInstance()->SceneVector;
}

FRotator& Y::GetRotation()
{
	return UY_GameInstance::YGI->NowRotator;
}

int32 Y::ExecutePureAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, FString TriggerAction, bool TryAttack)
{
	//FBuffLog BuffLog;
	//BuffLog.LogInit(FromCharacter, ToCharacter);
	//BuffLog.LogType = 1;
	int32 UsingCondition = ToBuffs.FindCondition();
	if (UsingCondition != 0) {
		if (IsValid(ToCharacter) && ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition >> 1), TriggerAction, TryAttack) == 0) {
			ToBuffs.ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, (UsingCondition), TriggerAction, TryAttack);
			if (ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::DetectDeath, TriggerAction, TryAttack) != 0
				&& ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::BeginDeath, TriggerAction, TryAttack) == 0) {
				ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterDeath, TriggerAction, TryAttack);
				ToCharacter->CharacterDead();
				ToBuffs.ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterKill, TriggerAction, TryAttack);
				if(IsValid(FromCharacter)){
					FromCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterKill, TriggerAction, TryAttack);
				}
			}
			else
				ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition << 1), TriggerAction, TryAttack);
		}
	}
	//FBuffLog::FightLogs.Add(MoveTemp(BuffLog));
	return UsingCondition;
}

int32 Y::ExecuteAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, FString TriggerAction, bool TryAttack)
{
	//FBuffLog BuffLog;
	//BuffLog.LogInit(FromCharacter, ToCharacter);
	//BuffLog.LogType = 0;
	if (FromCharacter != nullptr && !FromCharacter->CheckValid())return -1;
	if (ToCharacter != nullptr && !ToCharacter->CheckValid())return -2;
	int32 UsingCondition = ToBuffs.FindCondition();
	if (UsingCondition != 0) {
		if (FromCharacter == nullptr || FromCharacter->CheckValid() && FromCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition >> 2), TriggerAction, TryAttack) == 0) {
			if (ToCharacter == nullptr || ToCharacter->CheckValid() && ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition >> 1), TriggerAction, TryAttack) == 0) {
				ToBuffs.ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, (UsingCondition), TriggerAction, TryAttack);

				for (auto& p : ToBuffs.Buff) { p->AddToCharacter(ToCharacter,TryAttack); }
				if(ToCharacter->CheckValid() && ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::DetectDeath, TriggerAction, TryAttack) != 0
					&& ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::BeginDeath, TriggerAction, TryAttack) == 0){
					GetGameInfo()->PrepareDie(ToCharacter);
					ToCharacter->CharacterDead();
					ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterDeath, TriggerAction, TryAttack);
					ToBuffs.ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterKill, TriggerAction, TryAttack);
					FromCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterKill, TriggerAction, TryAttack);
					GetGameInfo()->DestroyCharacter(ToCharacter);	
				}
				if(ToCharacter->CheckValid())	ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition << 1), TriggerAction, TryAttack);
			}
			if(FromCharacter->CheckValid())FromCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition << 2), TriggerAction, TryAttack);
		}
	}

	if(FromCharacter->CheckValid())FromCharacter->Update();
	if (ToCharacter->CheckValid())ToCharacter->Update();
	//FBuffLog::FightLogs.Add(MoveTemp(BuffLog));
	return UsingCondition;
}

AY_Character*& Y::GetMainCharacter()
{
	return UY_GameInstance::YGI->MainCharacter;
}

AY_PlayerController*& Y::GetController()
{
	return AY_PlayerController::ThisPlayerController;
}

Y_Fighting* Y::GetGameInfo()
{
	return GetGameInstance()->FightInfo.Get();
}

AY_Floor*& Y::GetChoosedFloor()
{
	return GetPlayer()->ChoosedFloor;
}

AY_Card*& Y::GetChoosedCard()
{
	return GetPlayer()->ChoosedCard;
}

float Y::getRandom()
{
	GetGameInstance()->HaveRandoms++;
	return GetGameInstance()->RandomStream.GetFraction();
}

UWorld* Y::GetWorld()
{
	return GetController()->GetWorld();
}

UTexture2D* Y::LoadPicture(const FString& FilePath)
{
	return GetGameInstance()->LoadPicture(FilePath);
}

int32& Y::GetCurrentLevel()
{
	return Y::GetGameInstance()->CurrentLevel;
}

const TCHAR* Y::toS(FText ReadyText)
{
	return *(ReadyText.ToString());
}


