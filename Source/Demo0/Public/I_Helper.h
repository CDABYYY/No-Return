// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Y_Floor.h"

namespace I {
	bool CardRange(AY_Floor* GetFloor, int32 n);//查看地板是否在选择范围内

	int32 absPlus(int32 n);//绝对值

	int32 maxPlus(int32 a, int32 b);//最大值

	int32 minPlus(int32 a, int32 b);//最小值

	bool IsBlocked(class ::AY_Floor* GetFloor);//路径是否被阻挡

	void Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder);//AOE边界范围
};

