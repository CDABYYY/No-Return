// Fill out your copyright notice in the Description page of Project Settings.


#include "I_Helper.h"
#include "Y_Floor.h"
#include "Y.h"
#include "Y_Character.h"

using namespace I;


bool I::CardRange(AY_Floor* GetFloor, int32 n)
{
	int32 ToPos = GetFloor->SerialNumber;
	if (ToPos >= 0 && ToPos < Y::GetFloors().Num() && IsValid(Y::GetFloors()[ToPos]) &&
		absPlus(GetFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber) <= n) return true;
	else return false;
}

int32 I::absPlus(int32 n)
{
	if (n < 0) return -n;
	else return n;
}

int32 I::maxPlus(int32 a, int32 b)
{
	if (a > b) return a;
	else return b;
}

int32 I::minPlus(int32 a, int32 b)
{
	if (a < b) return a;
	else return b;
}

bool I::IsBlocked(AY_Floor* GetFloor)
{
	int32 maxnum = maxPlus(GetFloor->SerialNumber, Y::GetMainCharacter()->StandFloor->SerialNumber);
	int32 minnum = minPlus(GetFloor->SerialNumber, Y::GetMainCharacter()->StandFloor->SerialNumber);
	if (maxnum == GetFloor->SerialNumber)minnum++;
	else maxnum--;
	for (int i = minnum; i <= maxnum; i++)
	{
		if (!IsValid(GetFloor) || IsValid(Y::GetFloors()[i]->StandCharacter)) return true;
	}
	return false;
}

void I::Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder)
{
	leftBorder = tempFloorNum - n > 0 ? tempFloorNum - n : 0;
	rightBorder = tempFloorNum + n < Y::GetFloors().Num() ? tempFloorNum + n : Y::GetFloors().Num();
}