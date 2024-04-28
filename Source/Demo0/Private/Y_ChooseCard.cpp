// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_ChooseCard.h"
#include "Y_CardInfo.h"
#include "Y_CardW.h"

void UY_ChooseCard::AfterChoose()
{
	Info->AfterChoose(ChoosedCards);
}

void UY_ChooseCard::CardClicked(class UY_CardW* ClickedWidget)
{
	Info->CardClicked(ClickedWidget->CardInfo);
}

void UY_ChooseCard::LoadInfo(TSharedPtr<Y_ChooseCardInfo> ToLoadInfo)
{
	Info = ToLoadInfo;
	Info->Owner = this;
	for (int32 i = 0; i < Info->Cards.Num();i++) {
		auto NewCard = CreateShowCard((float)i/Info->Cards.Num() * 1000);
		NewCard->CardInfo = Info->Cards[i];
		NewCard->Init();
		CardWidgets.Add(NewCard);
	}
}

Y_ChooseCardInfo::Y_ChooseCardInfo()
{
}

Y_ChooseCardInfo::~Y_ChooseCardInfo()
{
}

void Y_ChooseCardInfo::CardClicked(TSharedPtr<class Y_CardInfo> ClickedInfo)
{
	if (!Owner->ChoosedCards.Contains(ClickedInfo)) {
		Owner->ChoosedCards.Add(ClickedInfo);
	}
	else {
		Owner->ChoosedCards.Remove(ClickedInfo);
	}
}

void Y_ChooseCardInfo::AfterChoose(TArray<TSharedPtr<class Y_CardInfo>> ChoosedCards)
{

}
