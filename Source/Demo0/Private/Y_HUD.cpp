// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_HUD.h"
#include "Y.h"
#include "Y_Character.h"


void UY_HUD::HUDInit()
{
	YGameInstance = Y::GetGameInstance();
}

float UY_HUD::GetProcess()
{
	if (IsValid(Y::GetMainCharacter())) {
		return (float)Y::GetMainCharacter()->Health / Y::GetMainCharacter()->MaxHealth;
	}
	return 0;
}
