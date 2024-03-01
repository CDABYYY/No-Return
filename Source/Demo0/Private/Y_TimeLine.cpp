// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_TimeLine.h"
#include "Y_Character.h"
#include "Y_Profile.h"
#include "Y_GameInstance.h"

UY_TimeLine* UY_TimeLine::YTimeLine = nullptr;

void UY_TimeLine::TimeLineInit()
{
	YTimeLine = this;
	GameInstance = UY_GameInstance::YGI;
}

