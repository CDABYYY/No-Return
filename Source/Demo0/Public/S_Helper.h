// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Y_Floor.h"

namespace S {
	bool CardRange(AY_Floor* GetFloor, int32 n);//查看地板是否在选择范围内

	int32 absPlus(int32 n);//绝对值

	int32 maxPlus(int32 a, int32 b);//最大值

	int32 minPlus(int32 a, int32 b);//最小值

	bool IsBlocked(AY_Floor* GetFloor);//路径是否被阻挡

	bool IsEnemy(AY_Floor* GetFloor);//地板是否有敌人

	bool IsMain(AY_Floor* GetFloor);//地板是否是主角

	int32 MaxDist(AY_Floor* GetFloor, int32 n, int32 right);//由该地板向某个方向移动的最大距离

	void Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder);//AOE边界范围

	void Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder, bool right);//单侧边界范围

	int32 End(int32 tempFloorNum, int32 n, bool right);//强制位移终点
};

