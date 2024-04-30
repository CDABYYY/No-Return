// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Equipment.h"
#include "Y_ClassBase.h"
#include "Y_Fighting.h"
#include "Y_Character.h"

Y_Equipment::Y_Equipment()
{
}

Y_Equipment::~Y_Equipment()
{
}

int32 Y_Equipment::GetPrice()
{
    return 100;
}

void Y_Equipment::Update()
{
}

void Y_Equipment::Play(bool Execute)
{
    Y_StatusBar TS{ Y::YMakeShared<ShieldBuff>(6) };
    ExecuteAction(GetOwner(), GetOwner(), TS, Execute);
}

void Y_Equipment::Equiped()
{
}

void Y_Equipment::UnEquiped()
{
}

AY_Character* Y_Equipment::GetOwner()
{
    return Y::GetMainCharacter();
}

void Y_Equipment::DrawCard(int32 DrawCount, bool Execute)
{
    if (Execute) {
        Y::GetGameInfo()->DrawCard(DrawCount);
    }
}

void Y_Equipment::Clicked()
{
    for (auto& f : Y::GetFloors()) {
        if (f != nullptr && AcceptFloor(f)) {
            f->SetColor(TEXT("Yellow"));
        }
    }
    GetOwner()->CharacterStatus = PressingStatus;
}

void Y_Equipment::ExecuteAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ExecuteBuffs, bool TryExecute)
{
    Y::ExecuteAction(FromCharacter, ToCharacter, ExecuteBuffs, EquipmentName.ToString(), TryExecute);
}

bool Y_Equipment::AcceptFloor(AY_Floor* GetFloor)
{
    return GetFloor == GetOwner()->StandFloor;
}
