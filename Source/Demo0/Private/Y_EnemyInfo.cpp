// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_EnemyInfo.h"
#include "Y_Character.h"
#include "Y_GameInstance.h"
#include "Y.h"

#include "Y_ClassBase.h"
#include "Y_Floor.h"

Y_EnemyInfo::Y_EnemyInfo()
{
    Actions.Add(MakeShared<Y_CharacterAction>());
}

Y_EnemyInfo::~Y_EnemyInfo()
{
}

void Y_EnemyInfo::Init(int32 Level)
{
    EnemyLevel = Level;
}

int32 Y_EnemyInfo::GetRandomAction()
{
    TArray<float> Weights;
    float TotalWeight = 0;
    for (auto& p : Actions) {
        float t = p.Get()->GetWeight();
        TotalWeight += t;
        Weights.Add(t);
    }
    float Choosed = Y::getRandom() * TotalWeight;
    for (int32 i = 0; i < Weights.Num();i++) {
        if (Choosed < Weights[i])return i;
        Choosed -= Weights[i];
    }
    return 0;
}

void Y_EnemyInfo::EnemyAttack()
{
    Actions[ChoosedAction]->ActionExecute();
    //(Owner->Buffs)->ExecuteBuffs(Owner, Owner, MakeShared<ActionBuff>(Actions[ChoosedAction]), Y_Buff::AfterAction, TEXT("AfterAction"));
    (Owner->Buffs)->ExecuteBuffs(Owner, Owner, *(Owner->Buffs), Y_Buff::AfterAction, TEXT("AfterAction"));
    if((Owner->Buffs)->ExecuteBuffs(Owner, Owner, *(Owner->Buffs), Y_Buff::BeginAction, TEXT("BeginAction")) == 0)
    {
        ChoosedAction = GetRandomAction();
        Actions[ChoosedAction]->ActionChoosed();
        Owner->CharacterAttackTime += (int32)(Actions[ChoosedAction]->CurrentCost * Owner->ActionRate * Y::GetGameInstance()->TopoRate);
        Owner->ChangeAttackTime(Owner->CharacterAttackTime);
    }
}

void Y_EnemyInfo::EnemyDead()
{
    GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Dead")); 
}

Y_CharacterAction::Y_CharacterAction()
{
    OriginalCost = CurrentCost = 10;
    ActionID = 0;
}

AY_Character* Y_CharacterAction::GetOwner()
{
    return OwnerEnemy->Owner;
}

void Y_CharacterAction::Init(Y_EnemyInfo* Owner)
{
    OwnerEnemy = Owner;
}

float Y_CharacterAction::GetRate()
{
    return (float)CurrentCost / OriginalCost;
}

float Y_CharacterAction::GetWeight()
{
    return Weight;
}

int32 Y_CharacterAction::GetCost()
{
    return CurrentCost;
}

void Y_CharacterAction::ActionChoosed()
{
    GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Action Choosed"));
}

void Y_CharacterAction::ActionExecute()
{
    GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Action Execute"));
}

void Y_CharacterAction::ExecuteAction(AY_Character* FromCharacter, AY_Character* ToCharacter, Y_StatusBar& ExecuteBuffs, bool TryExecute)
{
    Y::ExecuteAction(FromCharacter, ToCharacter, ExecuteBuffs, GetName().ToString(), TryExecute);
}

FText Y_CharacterAction::LogDescript()
{
    return FText::FromString(TEXT("Log"));
}

void Y_CharacterAction::Move(int32 Distance, bool Execute)
{
    Y_StatusBar S{ Y::YMakeShared<MoveBuff>(Distance) };
    ExecuteAction(GetOwner(), GetOwner(), S, Execute);
    if (Execute) {
        GetOwner()->CharacterLogicalMove(Y::GetFloors()[GetOwner()->StandFloor->SerialNumber + Distance]);
    }
}


FText Y_CharacterAction::GetName()
{
    return ActionName;
}

FText Y_CharacterAction::GetDescribe()
{
    return ActionDescribe;
}

