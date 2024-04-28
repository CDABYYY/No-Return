// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_CardH.h"
#include "Y_CardW.h"
#include "Y_CardInfo.h"
#include "Y.h"

void UY_CardH::Init()
{
	ChoosedCard = nullptr;
	Pressing = false;
}

void UY_CardH::Update()
{
	bool Choosed = false;
	int32 Pos = Cards.Find(ChoosedCard);
	const float MaxHeight = -100;
	const float MaxAngle = 30;
	const float ReservedHeight = 80;
	if (Pos < 0)Pos = Cards.Num() / 2;
	else Choosed = true;

	float XPos = 1920 / 2 - Cards.Num() * 50 - 50;
	if (Choosed)XPos -= 50;
	for (int32 i = 0; i < Pos;i++) {
		Cards[i]->ArrangePos(XPos + i * 100, MaxHeight * i / Pos + ReservedHeight, -MaxAngle * (Pos - i) / Pos ,0.5);
	}
	if (Pos <= Cards.Num()) {
		if (Choosed) {
			Cards[Pos]->ArrangePos(XPos + Pos * 100, MaxHeight - 25 + ReservedHeight, 0, 0.5);
			XPos += 100;
		}
		else {
			Cards[Pos]->ArrangePos(XPos + Pos * 100, MaxHeight + ReservedHeight, 0, 0.5);
		}
	}
	for (int32 i = Pos + 1; i < Cards.Num(); i++) {
		Cards[i]->ArrangePos(XPos + i * 100, MaxHeight * (Cards.Num() - i) / (Cards.Num() - Pos) + ReservedHeight, MaxAngle * (i - Pos) / (Cards.Num() - Pos), 0.5);
	}
}

void UY_CardH::RemoveCard(UY_CardW* ToRemoveCard)
{
	int32 Pos = Cards.Find(ToRemoveCard);
	if (Pos >= 0) {
		if (ChoosedCard == ToRemoveCard) {
			ChoosedCard = nullptr;
			Pressing = false;
		}
		Cards.RemoveAt(Pos);
		ToRemoveCard->CardInfo->OwnerWidget = nullptr;
		ToRemoveCard->RemoveFromParent();
		Update();
	}
}

void UY_CardH::Clear()
{
	for (auto& p : Cards)p->RemoveFromParent();
	Cards.Empty();
}

void UY_CardH::AddCard(TSharedPtr<class Y_CardInfo> Card)
{
	auto NewCard = CreateCard();
	NewCard->CardInfo = Card;
	NewCard->Init();
	NewCard->Owner = this;
	Cards.Add(NewCard);

	Update();
}

void UY_CardH::TestAdd()
{
	auto P = CreateCard();
	P->Owner = this;
	Cards.Add(P);
	Update();
}
