// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Helper.h"
#include "Y_Floor.h"
#include "Y.h"
#include "Y_Character.h"

using namespace S;


bool S::CardRange(AY_Floor* GetFloor, int32 n)
{
	int32 ToPos = GetFloor->SerialNumber;
	if (ToPos >= 0 && ToPos < Y::GetFloors().Num() && IsValid(Y::GetFloors()[ToPos]) &&
		absPlus(GetFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber) <= n) return true;
	else return false;
}

int32 S::absPlus(int32 n)
{
	if (n < 0) return -n;
	else return n;
}

int32 S::maxPlus(int32 a, int32 b)
{
	if (a > b) return a;
	else return b;
}

int32 S::minPlus(int32 a, int32 b)
{
	if (a < b) return a;
	else return b;
}

bool S::IsBlocked(AY_Floor* GetFloor)
{
	int32 maxnum = maxPlus(GetFloor->SerialNumber, Y::GetMainCharacter()->StandFloor->SerialNumber);
	int32 minnum = minPlus(GetFloor->SerialNumber, Y::GetMainCharacter()->StandFloor->SerialNumber);
	for (int32 i = minnum + 1; i < maxnum; i++)
	{
		if (!IsValid(GetFloor) || IsValid(Y::GetFloors()[i]->StandCharacter)) return true;
	}
	return false;
}

bool S::IsEnemy(AY_Floor* GetFloor)
{
	if (IsValid(GetFloor) && IsValid(GetFloor->StandCharacter) && GetFloor != Y::GetMainCharacter()->StandFloor)return true;
	return false;
}

bool S::IsMain(AY_Floor* GetFloor)
{
	if (GetFloor->SerialNumber == Y::GetMainCharacter()->StandFloor->SerialNumber) return true;
	return false;
}

int32 S::MaxDist(AY_Floor* GetFloor, int32 n, int32 Idirec)
{
	int32 step, count = 0;
	if (Idirec > 0)step = 1;
	else step = -1;
	for (int32 i = GetFloor->SerialNumber + step; 0 <= i && i < Y::GetFloors().Num() && count < n; i += step)
	{
		if (IsValid(Y::GetFloors()[i]) && !IsValid(Y::GetFloors()[i]->StandCharacter))
		{
			count++;
		}
		else {
			break;
		}
	}
	return count * step;
}

void S::Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder)
{
	leftBorder = tempFloorNum - n > 0 ? tempFloorNum - n : 0;
	rightBorder = tempFloorNum + n < Y::GetFloors().Num() ? tempFloorNum + n : Y::GetFloors().Num();
}

void S::Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder, bool right)
{
	if (right)
	{
		leftBorder = tempFloorNum + 1;
		rightBorder = tempFloorNum + n < Y::GetFloors().Num() ? tempFloorNum + n : Y::GetFloors().Num();
	}
	else
	{
		leftBorder = tempFloorNum - n > 0 ? tempFloorNum - n : 0;
		rightBorder = tempFloorNum - 1;
	}
}

int32 S::End(int32 tempFloorNum, int32 n, bool right)
{
	if (right)
	{
		for (int32 i = tempFloorNum + n; i >= tempFloorNum + n; i--)
		{
			if (!IsBlocked(Y::GetFloors()[i]) && !IsEnemy(Y::GetFloors()[i]))
			{
				return i;
			}
		}
	}
	else
	{
		for (int32 i = tempFloorNum - n; i <= tempFloorNum; i++)
		{
			if (!IsBlocked(Y::GetFloors()[i]) && !IsEnemy(Y::GetFloors()[i]))
			{
				return i;
			}
		}
	}
	return int32();
}

