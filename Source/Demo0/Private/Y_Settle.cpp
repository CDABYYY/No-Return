// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Settle.h"
#include "Y_PlayerController.h"
#include "Y_MapWidget.h"
#include "Y_Fighting.h"
#include "Y_Trophy.h"
#include "Y.h"

void UY_Settle::Init()
{
	Info = Y::GetGameInfo()->SettleInfo;
	Y::GetGameInfo()->SettleInfo = nullptr;
	Tittle = Info->Describe();
	for (auto& p : Info->TrophyInfos) {
		UY_Trophy* TP = CreateTrophy();
		TP->Info = p;
		TP->Init();
	}
}

void UY_Settle::EndWork()
{
	Info->EndWork();
	Y::GetGameInfo()->AfterFight();
	Y::GetController()->MapWidget->PullMap(false);
	Y::GetController()->ShowSettle(true);
}

void UY_Settle::LoadInfo(TSharedPtr<class Y_SettleInfo> LoadingInfo)
{
	Info = LoadingInfo;
	Tittle = Info->Describe();
	for (auto& p : Info->TrophyInfos) {
		auto TP = CreateTrophy();
		TP->LoadInfo(p);
		Trophys.Add(TP);
	}
}

Y_SettleInfo::Y_SettleInfo()
{
	TittleDescribe = FText::FromString(TEXT("Victory"));
}

FText Y_SettleInfo::Describe()
{
	return TittleDescribe;
}

void Y_SettleInfo::EndWork()
{
}
