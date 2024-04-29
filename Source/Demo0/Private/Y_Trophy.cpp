// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Trophy.h"
#include "Y.h"
#include "Y_ChooseCard.h"
#include "Y_PlayerController.h"

Y_TrophyInfo::~Y_TrophyInfo()
{
}

UTexture2D* Y_TrophyInfo::Picture()
{
	return UsingPicture;
}

FText Y_TrophyInfo::Describe()
{
	return UsingDescibe;
}

FText Y_TrophyInfo::Amount()
{
	if(Counts <= 1)
		return FText();
	return FText::FromString(FString::Printf(TEXT("%d"), Counts));
}

void Y_TrophyInfo::Clicked()
{
	Y::Log(0, TEXT("Click Trophy"));
}

void UY_Trophy::Clicked()
{
	if(Info.IsValid()){
		Info->Clicked();
		RemoveFromParent();
	}
}

void UY_Trophy::Init()
{
	UsingPicture = Info->Picture();
	TrophyDescribe = Info->Describe();
	TrophyAmount = Info->Amount();
}

void UY_Trophy::LoadInfo(TSharedPtr<class Y_TrophyInfo> LoadingInfo)
{
	Info = LoadingInfo;
	Init();
}

TSharedPtr<CardTrophy> CardTrophy::Share(std::initializer_list<TSharedPtr<class Y_CardInfo>> ToLoadInfos)
{
	auto p = new CardTrophy{ ToLoadInfos };
	TSharedPtr<CardTrophy> TP = TSharedPtr<CardTrophy>(p);
	return TP;
}

CardTrophy::CardTrophy(std::initializer_list<TSharedPtr<class Y_CardInfo>> ToLoadInfos)
{
	for (auto& p : ToLoadInfos)CardInfos.Add(p);
}

void CardTrophy::Clicked()
{
	auto ChooseInfo = MakeShared<Y_ChooseCardInfo>();
	ChooseInfo->Cards = CardInfos;
	Y::GetController()->BeginChoose(ChooseInfo);
}
