// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Trophy.h"
#include "Y.h"
#include "Y_ChooseCard.h"
#include "Y_PlayerController.h"
#include "Y_Fighting.h"
#include "Y_Equipment.h"

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

TSharedPtr<CardTrophy> CardTrophy::Share()
{
	auto p = new CardTrophy{ Y::GetGameInfo()->GetRandomCard(),Y::GetGameInfo()->GetRandomCard() ,Y::GetGameInfo()->GetRandomCard() };
	TSharedPtr<CardTrophy> TP = TSharedPtr<CardTrophy>(p);
	return TP;
}

CardTrophy::CardTrophy(std::initializer_list<TSharedPtr<class Y_CardInfo>> ToLoadInfos)
{
	for (auto& p : ToLoadInfos)CardInfos.Add(p);
}

void CardTrophy::Clicked()
{
	auto ChooseInfo = MakeShared<Y_ChooseCardIN>();
	ChooseInfo->Cards = CardInfos;
	Y::GetController()->BeginChoose(ChooseInfo);
}

FText CardTrophy::Describe()
{
	return Y::PrintText(TEXT("选择一张卡牌"));
}

TSharedPtr<EquipmentTrophy> EquipmentTrophy::Share(TSharedPtr<class Y_Equipment> ToLoadInfo)
{
	auto p = new EquipmentTrophy(ToLoadInfo);
	TSharedPtr<EquipmentTrophy> TP = TSharedPtr<EquipmentTrophy>(p);
	return TP;
}

TSharedPtr<EquipmentTrophy> EquipmentTrophy::Share()
{
	auto p = new EquipmentTrophy(Y::GetGameInfo()->GetRandomEquipment());
	TSharedPtr<EquipmentTrophy> TP = TSharedPtr<EquipmentTrophy>(p);
	return TP;
}

EquipmentTrophy::EquipmentTrophy(TSharedPtr<class Y_Equipment> ToLoadInfo)
{
	EquipmentInfo = ToLoadInfo;
	UsingPicture = EquipmentInfo->UsingPicture;
}

void EquipmentTrophy::Clicked()
{
	Y::GetGameInfo()->AddEquipment(EquipmentInfo);
}

FText EquipmentTrophy::Describe()
{
	return Y::PrintText(TEXT("获得装备： %s"), *(EquipmentInfo->EquipmentName.ToString()));
}

TSharedPtr<MoneyTrophy> MoneyTrophy::Share(int32 MoneyCount)
{
	auto p = new MoneyTrophy(MoneyCount);
	TSharedPtr<MoneyTrophy> TP = TSharedPtr<MoneyTrophy>(p);
	return TP;
}

MoneyTrophy::MoneyTrophy(int32 MoneyCount)
{
	Money = MoneyCount;
}

void MoneyTrophy::Clicked()
{
	Y::GetGameInfo()->AddMoney(Money);
}

FText MoneyTrophy::Describe()
{
	return Y::PrintText(TEXT("获得金币： %d"), Money);
}
