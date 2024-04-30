// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_EquipmentH.h"
#include "Y_EquipmentW.h"

void UY_EquipmentH::Init()
{
	ChoosedEquipment = nullptr;
	Pressing = false;
}

void UY_EquipmentH::Update()
{
	for (int32 i = 0; i < Equipments.Num();i++) {
		Equipments[i]->Update();
		Equipments[i]->SetPos(i * 100);
	}
}

void UY_EquipmentH::RemoveEquipment(UY_EquipmentW* ToRemoveEquipment)
{
	Equipments.Remove(ToRemoveEquipment);
	ToRemoveEquipment->RemoveFromParent();
}

void UY_EquipmentH::Clear()
{
	for (auto& p : Equipments)p->RemoveFromParent();
	Equipments.Empty();
}

void UY_EquipmentH::AddEquipment(TSharedPtr<class Y_Equipment> Equipment)
{
	auto NewEquipment = CreateEquipment();
	NewEquipment->Info = Equipment;
	NewEquipment->Init();
	NewEquipment->Owner = this;
	Equipments.Add(NewEquipment);

	Update();
}
