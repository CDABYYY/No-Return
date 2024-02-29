// Fill out your copyright notice in the Description page of Project Settings.


#include "YCard01.h"
#include "Y.h"
#include "Y_Floor.h"
#include "CameraPawn.h"
#include "Y_Character.h"

AYCard01::AYCard01() {
	CardShapeInit(TEXT("/Script/Engine.Material'/Game/Resource/Png/JayceE.JayceE'"));
	NowCost = 5;
	CardCost = 5;
}

void AYCard01::Play()
{
	Y::GetMainCharacter()->MyPlayMontage(TEXT("Attack3"), Y::GetPlayer()->ChoosedFloor, 1, false);
}

void AYCard01::Clicked()
{
	SetColor(TEXT("Blue"));
	for (auto&& f : Y::GetFloors()) {
		if (f != nullptr && AcceptFloor(f))
			f->SetColor(TEXT("Yellow"));
	}
}

bool AYCard01::AcceptFloor(AY_Floor* TargetFloor)
{
	AY_Floor* nowFloor = Y::GetMainCharacter()->StandFloor;
	if (TargetFloor != nullptr) {
		return TargetFloor->SerialNumber <= nowFloor->SerialNumber + 1 && TargetFloor->SerialNumber >= nowFloor->SerialNumber - 1;
	}
	return false;
}
