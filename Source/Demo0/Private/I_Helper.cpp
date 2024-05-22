// Fill out your copyright notice in the Description page of Project Settings.


#include "I_Helper.h"
#include "Y_Floor.h"
#include "Y.h"
#include "Y_Character.h"

using namespace I;


bool I::CardRange(AY_Floor* GetFloor, int32 n)
{
	int32 ToPos = GetFloor->SerialNumber;
	if (IsValid(Y::GetFloors()[ToPos]) &&
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
	for (int32 i = minnum + 1; i < maxnum; i++)
	{
		if (!IsValid(GetFloor) || IsValid(Y::GetFloors()[i]->StandCharacter)) return true;
	}
	return false;
}

bool I::IsEnemy(AY_Floor* GetFloor)
{
	if (IsValid(GetFloor) && GetFloor->StandCharacter->CheckValid() && GetFloor != Y::GetMainCharacter()->StandFloor)return true;
	return false;
}

int32 I::MaxDist(AY_Floor* GetFloor, int32 n, int32 Idirec)
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
	return count;
}

int32 I::PosAttack(AY_Floor* GetFloor, int32 n, int32 Idirect)
{
	int32 dist = Y::GetMainCharacter()->StandFloor->SerialNumber - GetFloor->SerialNumber;
	dist = absPlus(dist);
	if (dist <= n)return Y::GetMainCharacter()->StandFloor->SerialNumber;
	return GetFloor->SerialNumber + n * Idirect;
}

bool I::AccAttack(AY_Floor* AttackFloor)
{
	if (0 <= AttackFloor->SerialNumber && AttackFloor->SerialNumber <= Y::GetFloors().Num())
	{
		if (IsValid(AttackFloor) && IsValid(AttackFloor->StandCharacter))
		{
			return true;
		}
	}
	return false;
}

void I::Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder)
{
	leftBorder = tempFloorNum - n > 0 ? tempFloorNum - n : 0;
	rightBorder = tempFloorNum + n < Y::GetFloors().Num() ? tempFloorNum + n : Y::GetFloors().Num() - 1;
}

void I::Border(int32 tempFloorNum, int32 n, int32& leftBorder, int32& rightBorder, bool right)
{
	if (right)
	{
		leftBorder = tempFloorNum + 1;
		rightBorder = tempFloorNum + n < Y::GetFloors().Num() ? tempFloorNum + n : Y::GetFloors().Num() - 1;
	}
	else
	{
		leftBorder = tempFloorNum - n > 0 ? tempFloorNum - n : 0;
		rightBorder = tempFloorNum - 1;
	}
}

int32 I::End(int32 tempFloorNum, int32 n, bool right)
{
	if (right)
	{
		for (int32 i = tempFloorNum + n; i >= tempFloorNum; i--)
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
