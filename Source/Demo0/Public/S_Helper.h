// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Y_Floor.h"

namespace S {
	bool CardRange(AY_Floor* GetFloor, int32 n);//�鿴�ذ��Ƿ���ѡ��Χ��

	int32 absPlus(int32 n);//����ֵ

	int32 maxPlus(int32 a, int32 b);//���ֵ

	int32 minPlus(int32 a, int32 b);//��Сֵ

	bool IsBlocked(AY_Floor* GetFloor);//·���Ƿ��赲

	bool IsEnemy(AY_Floor* GetFloor);//�ذ��Ƿ��е���

	bool IsMain(AY_Floor* GetFloor);//�ذ��Ƿ�������

	int32 MaxDist(AY_Floor* GetFloor, int32 n, int32 right);//�ɸõذ���ĳ�������ƶ���������

	void Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder);//AOE�߽緶Χ

	void Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder, bool right);//����߽緶Χ

	int32 End(int32 tempFloorNum, int32 n, bool right);//ǿ��λ���յ�
};

