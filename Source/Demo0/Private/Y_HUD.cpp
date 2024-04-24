// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_HUD.h"
#include "Y.h"
#include "Y_Character.h"
#include "Y_Fighting.h"
#include "Y_CardInfo.h"
#include "CameraPawn.h"


void UY_HUD::FlowMessage(FText NewMessage, int32 color)
{
	FlowingMessage = NewMessage;
	NoticeMessage(TEXT(""), color);
}

void UY_HUD::HUDInit()
{
	YGameInstance = Y::GetGameInstance();
}

float UY_HUD::GetProcess()
{
	if (IsValid(Y::GetMainCharacter())) {
		return (float)Y::GetMainCharacter()->Health / Y::GetMainCharacter()->MaxHealth;
	}
	return 0;
}

void UY_HUD::ExecuteSkill()
{
	if(Y::GetPlayer()->ClickAble){
		auto& ChoosedCard = Y::GetGameInfo()->MCSkill;
		ChoosedCard->Play();
		Y::GetMainCharacter()->CharacterAttackTime += ChoosedCard->CurrentCost;
		Y::GetMainCharacter()->ChangeAttackTime(Y::GetMainCharacter()->CharacterAttackTime);
		Y::GetPlayer()->ClickAble = false;
	}
}
