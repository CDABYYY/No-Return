// Fill out your copyright notice in the Description page of Project Settings.


#include "Y.h"
#include "Y_GameInstance.h"

Y::Y()
{
}

Y::~Y()
{
}

UY_GameInstance* Y::GetGameInstance()
{
	return UY_GameInstance::YGI;
}

ACameraPawn* Y::GetPlayer()
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

AY_Character* Y::GetMainCharacter()
{
	return UY_GameInstance::YGI->MainCharacter;
}
