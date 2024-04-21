// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_TimeLine.h"
#include "Y_Character.h"
#include "Y_Profile.h"
#include "Y_TimeMark.h"
#include "Y_GameInstance.h"

UY_TimeLine* UY_TimeLine::YTimeLine = nullptr;

void UY_TimeLine::TimeLineInit()
{
	YTimeLine = this;
	GameInstance = UY_GameInstance::YGI;

	TimeMarks.reset([](UY_TimeMark*& a1, UY_TimeMark*& a2) 
		{return a1->ExecuteTime < a2->ExecuteTime; });
}

void UY_TimeLine::EndRoom()
{
	for (auto& p : TimeMarks) {
		p->RemoveFromParent();
	}
	TimeMarks.Data.Empty();
}

void UY_TimeLine::AddCharacter(AY_Character* AddedCharacter)
{
	for (auto& p : TimeMarks) {
		if (p->ExecuteTime == AddedCharacter->CharacterAttackTime) {
			p->AddProfile(AddedCharacter);
			return;
		}
	}
	UY_TimeMark* tm = NewTimeMark();
	tm->TimeMarkInit();
	tm->Owner = this;
	tm->ExecuteTime = AddedCharacter->CharacterAttackTime;
	tm->AddProfile(AddedCharacter);
	TimeMarks.Add(tm);
}

void UY_TimeLine::RemoveCharacter(AY_Character* RemovedCharacter)
{
	for (auto& p : TimeMarks) {
		p->RemoveProfile(RemovedCharacter);
	}
}

void UY_TimeLine::UpdateTimeMark()
{
	if (TimeMarks.Num() != 0 && UY_GameInstance::YGI->RunTime * 10 > (*(TimeMarks.begin()))->ExecuteTime) {
		(*TimeMarks.begin())->ExecuteMark();
		//TimeMarks.RemoveFirst(*TimeMarks.begin());
	}
}


