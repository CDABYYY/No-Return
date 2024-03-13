// Fill out your copyright notice in the Description page of Project Settings.


#include "Y.h"
#include "Y_GameInstance.h"
#include "Y_StatusBar.h"
#include "Y_Character.h"

Y::Y()
{
}

Y::~Y()
{
}

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

TArray<class AY_Enemy*>& Y::GetEnemys()
{
	return UY_GameInstance::YGI->Enemys;
}

FVector& Y::GetLocation()
{
	return UY_GameInstance::YGI->NowVector;
}

FRotator& Y::GetRotation()
{
	return UY_GameInstance::YGI->NowRotator;
}

int32 Y::ExecutePureAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, FString TriggerAction, bool TryAttack)
{
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
	return UsingCondition;
}

int32 Y::ExecuteAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ToBuffs, FString TriggerAction, bool TryAttack)
{
	int32 UsingCondition = ToBuffs.FindCondition();
	if (UsingCondition != 0) {
		if (IsValid(FromCharacter) && FromCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition >> 2), TriggerAction, TryAttack) == 0) {
			if (IsValid(ToCharacter) && ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition >> 1), TriggerAction, TryAttack) == 0) {
				ToBuffs.ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, (UsingCondition), TriggerAction, TryAttack);
				if(ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::DetectDeath, TriggerAction, TryAttack) != 0
					&& ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::BeginDeath, TriggerAction, TryAttack) == 0){
					ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterDeath, TriggerAction, TryAttack);
					ToCharacter->CharacterDead();
					ToBuffs.ExecuteBuffs(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterKill, TriggerAction, TryAttack);
					FromCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, Y_Buff::AfterKill, TriggerAction, TryAttack);
				}
				else
					ToCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition << 1), TriggerAction, TryAttack);
			}
			FromCharacter->ExecuteAction(FromCharacter, ToCharacter, ToBuffs, (UsingCondition << 2), TriggerAction, TryAttack);
		}
	}
	return UsingCondition;
}

AY_Character*& Y::GetMainCharacter()
{
	return UY_GameInstance::YGI->MainCharacter;
}

float Y::getRandom()
{
	GetGameInstance()->HaveRandoms++;
	return GetGameInstance()->RandomStream.GetFraction();
}


