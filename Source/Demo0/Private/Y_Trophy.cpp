// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Trophy.h"
#include "Y.h"

UTexture2D* Y_TrophyInfo::Picture()
{
	return nullptr;
}

FText Y_TrophyInfo::Describe()
{
	return FText();
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
	Info->Clicked();
	RemoveFromParent();
}

void UY_Trophy::Init()
{
	UsingPicture = Info->Picture();
	TrophyDescribe = Info->Describe();
	TrophyAmount = Info->Amount();
}
