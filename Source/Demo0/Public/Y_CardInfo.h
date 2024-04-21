// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DEMO0_API Y_CardInfo
{
public:

	virtual int32 GetCost();

	virtual float GetRate();

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

	int32 Weight = 0;

	class AY_Card* Owner;

	void CardUpdate();

	virtual FText LogDescript();

	virtual void Play();

	virtual void Drawed();

	virtual void Discarded();

	virtual void Leave();

	virtual void Clicked();

	virtual float GetWeight();

	virtual bool AcceptFloor(class AY_Floor* GetFloor);
};
