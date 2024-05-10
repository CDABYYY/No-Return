// Fill out your copyright notice in the Description page of Project Settings.


#include "A01.h"
#include "Y_ClassBase.h"
#include "Y_Character.h"
#include "Y_Fighting.h"
#include "CameraPawn.h"
#include "Y_EventWidget.h"
#include "Y_ChoiceWidget.h"
#include "Y_PlayerController.h"
#include "Y_Settle.h"
#include "Y_Trophy.h"
#include "Y_Equipment.h"
#include "Y.h"

BurstBurn::BurstBurn()
{
	BuffAsType = BuffID = 9;
	TriggerCondition = 0;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("Òý±¬"));
}

void BurstBurn::AddToCharacter(AY_Character* TargetCharacter, bool Execute)
{
	auto TA = TargetCharacter->Buffs->FindType(5);
	Y_StatusBar TS;
	for (auto& p : TA)p->execute(TargetCharacter, TargetCharacter, TS, Ticking, BuffName.ToString(), Execute);
}

B11::B11()
{
	BuffAsType = BuffID = 11;
	TriggerCondition = 0;
	BuffProperty = 3;
	BuffOrder = 0;
	BuffLevel = -5;
	BuffExtend.Add(BuffID);
	BuffName = Y::PrintText(TEXT("²»Ï¢"));
}

void B11::AddToCharacter(AY_Character* TargetCharacter, bool Execute)
{
	if (Execute) {
		auto TA = OwnerCharacter->Buffs->FindType(5);
		for (auto& p : TA)p->BuffParams[0] = 1;
	}
}

