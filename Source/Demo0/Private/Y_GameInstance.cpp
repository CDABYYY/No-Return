// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_GameInstance.h"
#include "Y_Character.h"

ACameraPawn* UY_GameInstance::YC = nullptr;
TArray<AY_Card*> UY_GameInstance::Cards;
TArray<AY_Floor*> UY_GameInstance::Floors;
AY_Character* UY_GameInstance::MainCharacter = nullptr;

UY_GameInstance::UY_GameInstance()
{
	Cards.SetNum(10);
	Floors.SetNum(20);
	for (auto& p : Cards)p = nullptr;
	for (auto& p : Floors)p = nullptr;
}