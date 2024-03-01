// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Profile.h"
#include "Y_Character.h"
#include "Y.h"
#include "Y_GameInstance.h"

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
