// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_EquipmentW.h"
#include "Y_Equipment.h"
#include "Y_EquipmentH.h"

void UY_EquipmentW::Init()
{
	Update();
}

void UY_EquipmentW::Update()
{
	if (Info.IsValid()) {
		Info->Owner = this;
		Picture = Info->UsingPicture;
		//Need Fix :Havn't Dill Lop Cd follow Run
		EquipmentCD = Info->SkillCD;
		EquipmentID = Info->EquipmentID;
		EquipmentCount = Info->CanUseCount;
	}
}

void UY_EquipmentW::Enter()
{
}

void UY_EquipmentW::Leave()
{
}

void UY_EquipmentW::Press()
{
	if (IsValid(Owner))
	{
		Owner->ChoosedEquipment = this;
		Owner->Pressing = true;
		Owner->Update();

		Info->Clicked();
	}
}

void UY_EquipmentW::HelpTick(float DeltaTime)
{
}
