// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_ChooseCard.h"
#include "Y_CardInfo.h"
#include "Y_PlayerController.h"
#include "Y_CardW.h"
#include "Y.h"
#include "Y_Fighting.h"

void UY_ChooseCard::AfterChoose()
{
	Info->AfterChoose(ChoosedCards);
	Y::GetController()->ShowChoosing(true);
}

void UY_ChooseCard::CardClicked(class UY_CardW* ClickedWidget)
{
	if(ChoosedCards.Num() < Info->ChooseCount)
	{
		Info->CardClicked(ClickedWidget->CardInfo);
		FString ToDiscribe = Info->ChooseDiscribe;
		ToDiscribe.Append(FString::Printf(TEXT(" : %d / %d"), ChoosedCards.Num(), Info->ChooseCount));
		Discribe = FText::FromString(ToDiscribe);
	}
}

void UY_ChooseCard::LoadInfo(TSharedPtr<Y_ChooseCardInfo> ToLoadInfo)
{
	for (auto& p : CardWidgets)if (IsValid(p))p->RemoveFromParent();
	Info = ToLoadInfo;
	Info->Owner = this;
	for (int32 i = 0; i < Info->Cards.Num();i++) {
		auto NewCard = CreateShowCard(i);
		NewCard->CardInfo = Info->Cards[i];
		NewCard->Init();
		CardWidgets.Add(NewCard);
	}
	FString ToDiscribe = Info->ChooseDiscribe;
	ToDiscribe.Append(FString::Printf(TEXT(" : 0 / %d"), Info->ChooseCount));
	Discribe = FText::FromString(ToDiscribe);
}

Y_ChooseCardInfo::Y_ChooseCardInfo()
{
	ChooseCount = 1;
	ChooseDiscribe = TEXT("请选择卡牌");
	NeedChooseMax = false;
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

void Y_ChooseCardIN::AfterChoose(TArray<TSharedPtr<class Y_CardInfo>> ChoosedCards)
{
	for (auto& p : ChoosedCards) {
		Y::GetGameInfo()->UsingCards.Add(p);
	}
}

void Y_ChooseCardOut::AfterChoose(TArray<TSharedPtr<class Y_CardInfo>> ChoosedCards)
{
	for (auto& p : ChoosedCards) {
		Y::GetGameInfo()->UsingCards.Remove(p);
	}
}
