// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_EnemyInfo.h"

/**
 * 
 */
class DEMO0_API Y_CardInfo:public Y_CharacterAction,public TSharedFromThis<Y_CardInfo>
{
public:

	virtual int32 GetCost();

	virtual float GetRate()override;

	virtual FText GetCardDescribe();

	virtual FText GetPointDescribe();

	virtual FName GetMontageName();

	virtual UTexture2D* GetPicture();

	virtual FText GetName();

public:
	Y_CardInfo();
	virtual ~Y_CardInfo();

	int32 UsedType;
	int32 CardID;
	FText CardName;
	FText CurrentCardDescribe;
	FText CurrentPointDescribe;

	// Extend From Action

	//int32 OriginalCost;
	//int32 CurrentCost;
	//FName UsingMontageName;
	//UTexture2D* UsingPicture;

	//The Status when Pressing this Card
	int32 PressingStatus;

	int32 CardWeight;

	//Normal 1, Rare 2, Super Rare 3
	int32 CardRare;

	int32 CostMoney;

	TSet<int32> CardTypes;

	bool NeedTarget;

	class AY_Card* Owner;

	class UY_CardW* OwnerWidget;

	virtual class AY_Character* GetOwner();

	virtual void BindMessage(FString Name);

	virtual void CardUpdate();

	virtual void ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ExecuteBuffs, bool TryExecute);

	virtual void Move(int32 Distance, bool Execute);

	virtual void PlayNiagara(FName PlayName,bool Execute, int32 ToPosition = 0, float Duration = -1, AY_Floor* BeginFloor = nullptr);

	static void DrawCard(int32 DrawCount,bool Execute);
	
	virtual FText LogDescript();

	virtual void AddToCards(int32 InType);

	virtual void RemoveFromCards(int32 InType);

	virtual void Play(bool Execute);

	virtual void Drawed();

	virtual void Discarded();

	virtual void Leave();

	virtual void Clicked();

	virtual float GetWeight();

	virtual void BeginFighting();

	virtual bool AcceptFloor(class AY_Floor* GetFloor);
};
