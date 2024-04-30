// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_CardInfo.h"
#include "Y_Card.h"
#include "Y.h"
#include "Y_Character.h"
#include "Y_Floor.h"
#include "Y_GameInstance.h"
#include "CameraPawn.h"
#include "Y_Fighting.h"

#include "Y_ClassBase.h"

int32 Y_CardInfo::GetCost()
{
	return OriginalCost;
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

FText Y_CardInfo::GetName()
{
	return CardName;
}

Y_CardInfo::Y_CardInfo()
{
	CurrentCost = OriginalCost = 10;
	UsedType = 0;
	CardID = 0;

	NeedTarget = true;
	PressingStatus = 1;

	FString Path = TEXT("/Script/Engine.Texture2D'/Game/Resource/Png/JayceStaticField.JayceStaticField'");
	UsingPicture = Y::LoadPicture(Path);
}

Y_CardInfo::~Y_CardInfo()
{
}


AY_Character* Y_CardInfo::GetOwner()
{
	return Y::GetMainCharacter();
}

void Y_CardInfo::CardUpdate()
{
	CurrentCost = GetCost();

	CurrentCardDescribe = GetCardDescribe();

	UsingMontageName = GetMontageName();

	UsingPicture = GetPicture();
}

void Y_CardInfo::ExecuteAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ExecuteBuffs, bool TryExecute)
{
	Y::ExecuteAction(FromCharacter, ToCharacter, ExecuteBuffs, GetName().ToString(), TryExecute);
}

void Y_CardInfo::Move(int32 Distance, bool Execute)
{
	Y_StatusBar S{ Y::YMakeShared<MoveBuff>(Distance) };
	ExecuteAction(Y::GetMainCharacter(), Y::GetMainCharacter(), S, Execute);
	if (Execute) {
		Y::GetMainCharacter()->CharacterLogicalMove(Y::GetFloors()[Y::GetMainCharacter()->StandFloor->SerialNumber + Distance]);
	}
}

void Y_CardInfo::DrawCard(int32 DrawCount, bool Execute)
{
	if (Execute) {
		Y::GetGameInfo()->DrawCard(DrawCount);
	}
}

FText Y_CardInfo::LogDescript()
{
	return FText::FromString(TEXT("Card Log"));
}

void Y_CardInfo::AddToCards(int32 InType)
{
}

void Y_CardInfo::RemoveFromCards(int32 InType)
{
}

void Y_CardInfo::Play(bool Execute)
{
	UY_GameInstance::YGI->MainCharacter->MyPlayMontage(TEXT("Attack4"), UY_GameInstance::YGI->YC->ChoosedFloor, 1, Execute);
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
	GetOwner()->CharacterStatus = PressingStatus;
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
