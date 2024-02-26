// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_GameInstance.h"
#include "Y_Character.h"
#include "CameraPawn.h"
#include "Y_Card.h"
#include "Y_Floor.h"

UY_GameInstance* UY_GameInstance::YGI = nullptr;

UY_GameInstance::UY_GameInstance()
{
	YGI = this;
	Cards.SetNum(10);
	Floors.SetNum(20);
	for (auto& p : Cards)p = nullptr;
	for (auto& p : Floors)p = nullptr;
}