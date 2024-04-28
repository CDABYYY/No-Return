// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_UserWidget.h"
#include "Y_Character.h"
#include "Y_EnemyInfo.h"
#include "Y.h"

void UY_UserWidget::ShowBuffs()
{
	FString ToDiscribe;
	for (auto& p : OwnerCharacter->ShowBuffs->Buff) {
		ToDiscribe.Append(p->PrinCount());
	}
	BuffDiscribe = FText::FromString(ToDiscribe);
}

void UY_UserWidget::ClearShow()
{
	OwnerCharacter->ShowBuffs->Buff.Empty();
	BuffDiscribe = FText::GetEmpty();
}

void UY_UserWidget::UpdateAction()
{
	ActionPicture = OwnerCharacter->Info->Actions[OwnerCharacter->Info->ChoosedAction]->GetPicture();
	ActionTime = FText::FromString(FString::Printf(TEXT("%d"),(int32)(OwnerCharacter->CharacterAttackTime - Y::GetRunTime() * 10)));
}


void UY_UserWidget::UserWidgetInit(AY_Character* Owner)
{
	OwnerCharacter = Owner;
	//Temp
	BuffDiscribe = FText::FromString(TEXT("Init UW"));
}

float UY_UserWidget::GetHealthPersent()
{
	if (IsValid(OwnerCharacter)) {
		return (float)OwnerCharacter->Health / OwnerCharacter->MaxHealth;
	}
	return 0.0f;
}
