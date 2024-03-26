// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Profile.h"
#include "Y_Character.h"
#include "Y.h"
#include "Y_GameInstance.h"
#include "Y_TimeMark.h"
#include "Y_PlayerController.h"
#include "Y_TimeLine.h"
#include "Y_HUD.h"

int UY_Profile::GetRelativePosition()
{
	return (*AttackTime - *RunTime * 10) * 10;
}

void UY_Profile::ProfileInit(AY_Character* ReadCharacter)
{
	Character = ReadCharacter;
	RunTime = &(Y::GetGameInstance()->RunTime);
	AttackTime = &(ReadCharacter->CharacterAttackTime);
}

void UY_Profile::ChangeAttackTime(int32 ChangedTime)
{
	TimeOwner->RemoveProfile(Character);
	AY_PlayerController::ThisPlayerController->PCHUD->TimeLine->AddCharacterProfile(Character);
}
