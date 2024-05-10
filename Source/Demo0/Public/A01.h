// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Y_Buff.h"

//ID 10, ��ȼ��ɫ���ϵ�Buff
class DEMO0_API BurstBurn :public Y_Buff {
public:
	BurstBurn();
	virtual void AddToCharacter(class AY_Character* TargetCharacter, bool Execute);
};

//ID 11, Burn���ٽ��� Need Fix
class DEMO0_API B11 :public Y_Buff {
public:
	B11();
	virtual void AddToCharacter(class AY_Character* TargetCharacter, bool Execute);
};

