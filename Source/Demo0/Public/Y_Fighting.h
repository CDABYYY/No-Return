// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YOArray.h"
#include "Y_StatusBar.h"

/**
 * 
 */
class DEMO0_API Y_Fighting
{
public:
	Y_Fighting();
	~Y_Fighting();
	
	//Equipments And Buffs Will Only Run On BeginFight, AfterFight, CharacterSpawn
	//If you want to Add Trigger To Other Times, Put it On Character when CharacterSpawn so it will run
	YOArray<class Y_Equipment*> Equipments;

	//This is for Event. Recommand to Delete it when end event.
	Y_StatusBar EventBuffs;
	Y_StatusBar EquipmentsBuffs;
};
