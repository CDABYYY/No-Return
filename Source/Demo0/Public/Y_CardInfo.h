// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_EnemyInfo.h"

/**
 * 
 */
class DEMO0_API Y_CardInfo:public Y_CharacterAction
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

	int32 OriginalCost;
	int32 CurrentCost;
	FName UsingMontageName;
	FText CardName;
	UTexture2D* UsingPicture;
	FText CurrentCardDescribe;
	FText CurrentPointDescribe;

	//The Status when Pressing this Card
	int32 PressingStatus;

	int32 Weight = 0;

	bool NeedTarget;

	class AY_Card* Owner;

	class UY_CardW* OwnerWidget;

	virtual class AY_Character* GetOwner();

	virtual void CardUpdate();

	virtual void ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ExecuteBuffs, bool TryExecute);

	virtual void Move(int32 Distance, bool Execute);

	static void DrawCard(int32 DrawCount,bool Execute);
	
	virtual FText LogDescript();

	virtual void Play(bool Execute);

	virtual void Drawed();

	virtual void Discarded();

	virtual void Leave();

	virtual void Clicked();

	virtual float GetWeight();

	virtual bool AcceptFloor(class AY_Floor* GetFloor);
};
