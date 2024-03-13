// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_UserWidget.h"
#include "Y_Character.h"

void UY_UserWidget::UserWidgetInit(AY_Character* Owner)
{
	OwnerCharacter = Owner;
}

float UY_UserWidget::GetHealthPersent()
{
	if (IsValid(OwnerCharacter)) {
		return (float)OwnerCharacter->Health / OwnerCharacter->MaxHealth;
	}
	return 0.0f;
}
