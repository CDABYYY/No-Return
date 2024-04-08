// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Buff.h"
/**
 * 
 */
class DEMO0_API Y_Equipment
{
public:
	Y_Equipment();
	~Y_Equipment();
	TSharedPtr<Y_Buff> EquipmentBuff;
	int32 EquipmentPriority;
	int32 GetPrice();
	void Equiped();
	//TSharedPtr<Y_Buff> AddInFight();
	void UnEquiped();
};
