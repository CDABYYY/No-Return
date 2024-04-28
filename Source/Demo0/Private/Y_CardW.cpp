// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_CardW.h"
#include "Y_CardInfo.h"
#include "Y_CardH.h"
#include "Y_PlayerController.h"
#include "Y.h"

void UY_CardW::Init()
{
	NowXPos = 2000;
	NowYPos = 0;
	NowAngle = 0;
	Update();
}

void UY_CardW::Update()
{
	if (CardInfo.IsValid()) {
		CardInfo->OwnerWidget = this;
		CardName = CardInfo->GetName();
		CardDescribe = CardInfo->GetCardDescribe();
		Cost = CardInfo->GetCost();
		Picture = CardInfo->GetPicture();
	}
}

void UY_CardW::Enter()
{
	if(IsValid(Owner))
	{
		Owner->ChoosedCard = this;
		Owner->Update();
	}
}

void UY_CardW::Leave()
{
	if (IsValid(Owner) && Owner->ChoosedCard == this && !Owner->Pressing)
	{
		Owner->ChoosedCard = nullptr;
		Owner->Update();
	}
}

void UY_CardW::Press()
{
	if(IsValid(Owner))
	{
		Owner->ChoosedCard = this;
		Owner->Pressing = true;
		Owner->Update();
		Y::GetController()->ShowCards(true);

		CardInfo->Clicked();
	}
}

void UY_CardW::HelpTick(float DeltaTime)
{
	if (LivingTime > 0) {
		if (LivingTime < DeltaTime) {
			NowXPos = ToXPos;
			NowYPos = ToYPos;
			NowAngle = ToAngle;
			LivingTime = 0;
		}
		else {
			NowXPos += (ToXPos - NowXPos) * DeltaTime / LivingTime;
			NowYPos += (ToYPos - NowYPos) * DeltaTime / LivingTime;
			NowAngle += (ToAngle - NowAngle) * DeltaTime / LivingTime;
			LivingTime -= DeltaTime;
		}
		SetPos(NowXPos, NowYPos, NowAngle);
	}
}

void UY_CardW::ArrangePos(float XPos, float YPos, float Angle, float Time)
{
	ToXPos = XPos;
	ToYPos = YPos;
	ToAngle = Angle;
	LivingTime = Time;
}
