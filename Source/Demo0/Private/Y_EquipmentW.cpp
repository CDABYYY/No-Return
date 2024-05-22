// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_EquipmentW.h"
#include "Y_Equipment.h"
#include "Y_EquipmentH.h"

void UY_EquipmentW::Init()
{
	if (Info.IsValid()) {
		//Temp
		FString Name = FString::Printf(TEXT("%d"), Info->EquipmentID);
		FString Path = TEXT("/Script/Engine.Texture2D'/Game/Resource/EquipmentPictures/");
		Path.Append(Name);
		Path.Append(TEXT("."));
		Path.Append(Name);
		Path.Append(TEXT("'"));
		auto P = LoadObject<UTexture2D>(nullptr, Path.GetCharArray().GetData());
		if (IsValid(P))Picture = P;
	}
	Update();
}

void UY_EquipmentW::Update()
{
	if (Info.IsValid()) {
		Info->Owner = this;
		//Picture = Info->UsingPicture;
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
