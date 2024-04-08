// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_CardInfo.h"
#include "Y_Card.h"
#include "Y.h"
#include "Y_Character.h"
#include "Y_Floor.h"
#include "Y_GameInstance.h"
#include "CameraPawn.h"
#include "Y_Fighting.h"

int32 Y_CardInfo::GetCost()
{
	return CurrentCost;
}

float Y_CardInfo::GetRate()
{
	return	(float)CurrentCost / OriginalCost;
}

FText Y_CardInfo::GetCardDescribe()
{
	return CurrentCardDescribe;
}

FText Y_CardInfo::GetPointDescribe()
{
	return CurrentPointDescribe;
}

FName Y_CardInfo::GetMontageName()
{
	return UsingMontageName;
}

UTexture2D* Y_CardInfo::GetPicture()
{
	return UsingPicture;
}

Y_CardInfo::Y_CardInfo()
{
	CurrentCost = OriginalCost = 10;
}

Y_CardInfo::~Y_CardInfo()
{
}


void Y_CardInfo::CardUpdate()
{
	CurrentCost = GetCost();

	CurrentCardDescribe = GetCardDescribe();

	UsingMontageName = GetMontageName();

	UsingPicture = GetPicture();
}

FText Y_CardInfo::LogDescript()
{
	return FText::FromString(TEXT("Card Log"));
}

void Y_CardInfo::Play()
{
	UY_GameInstance::YGI->MainCharacter->MyPlayMontage(TEXT("Attack4"), UY_GameInstance::YGI->YC->ChoosedFloor, 1, true);
	Y::GetMainCharacter()->CharacterLogicalMove(Y::GetPlayer()->ChoosedFloor);
	Y::GetGameInfo()->DrawCard();
}

void Y_CardInfo::Drawed()
{
}

void Y_CardInfo::Discarded()
{
}

void Y_CardInfo::Leave()
{
}

void Y_CardInfo::Clicked()
{
	for (auto& f : Y::GetFloors()) {
		if (f!=nullptr && AcceptFloor(f)) {
			f->SetColor(TEXT("Yellow"));
		}
	}
}

float Y_CardInfo::GetWeight()
{
	return 10;
}

bool Y_CardInfo::AcceptFloor(AY_Floor* GetFloor)
{
	if (GetFloor == Y::GetMainCharacter()->StandFloor)return true;
	return false;
}
