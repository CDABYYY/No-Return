// Fill out your copyright notice in the Description page of Project Settings.


#include "YCard02.h"
#include "Y.h"
#include "Y_Floor.h"
#include "CameraPawn.h"
#include "Y_Character.h"

AYCard02::AYCard02() {
	CardShapeInit(TEXT("/Script/Engine.Material'/Game/Resource/Png/JayceW.JayceW'"));
	NowCost = 5;
	CardCost = 5;
}

void AYCard02::Play()
{
	auto i0 = Y::GetPlayer()->ChoosedFloor->SerialNumber;
	if(Y::GetPlayer()->ChoosedFloor->SerialNumber > Y::GetMainCharacter()->StandFloor->SerialNumber)
		Y::GetMainCharacter()->MyPlayMontage(TEXT("Attack1"), Y::GetFloors()[i0 - 1], 1, true);
	else
		Y::GetMainCharacter()->MyPlayMontage(TEXT("Attack1"), Y::GetFloors()[i0 + 1], 1, true);
}

void AYCard02::Clicked()
{
	SetColor(TEXT("Blue"));
	for (auto&& f : Y::GetFloors()) {
		if (f != nullptr && AcceptFloor(f))
			f->SetColor(TEXT("Yellow"));
	}
}

bool AYCard02::AcceptFloor(AY_Floor* TargetFloor)
{
	AY_Floor* nowFloor = Y::GetMainCharacter()->StandFloor;
	if (IsValid(TargetFloor)) {
		int32 i0 = Y::GetMainCharacter()->StandFloor->SerialNumber;
		int32 j0 = TargetFloor->SerialNumber;
		if (i0 > j0)Swap(i0, j0);
		if (i0 + 2 > j0 || i0 == j0)return false;
		for (i0 = i0 + 1; i0 < j0 && i0 < i0 + 2; i0++) {
			if (IsValid(Y::GetFloors()[i0]) && IsValid(Y::GetFloors()[i0]->StandCharacter))
				return false;
		}
		if (IsValid(TargetFloor->StandCharacter))return true;
	}
	return false;
}
