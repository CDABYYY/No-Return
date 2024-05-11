// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_TimeMark.h"
#include "Y_Profile.h"
#include "Y_GameInstance.h"
#include "Y_Character.h"
#include "Y_TimeLine.h"


float UY_TimeMark::GetRelativePosition()
{
	return ((float)ExecuteTime - UY_GameInstance::YGI->RunTime * 10) * 10;
}

void UY_TimeMark::TimeMarkInit()
{
	Profiles.reset([](AY_Character* a1, AY_Character* a2)
		{return a1->CharacterPriority > a2->CharacterPriority; });
}

void UY_TimeMark::AddProfile(AY_Character* ProfileAdded)
{
	Profiles.Add(ProfileAdded);
}

void UY_TimeMark::RemoveProfile(AY_Character* ProfileRemoved)
{
	Profiles.RemoveFirst(ProfileRemoved);
	if (Profiles.Num() == 0) {
		UY_TimeMark* TM = this;
		Owner->TimeMarks.RemoveFirst(TM);
		RemoveFromParent();
	}
}

void UY_TimeMark::ExecuteMark()
{
	if (Profiles.Num() != 0) {
		auto& p = *(Profiles.begin());
		if(p->CheckValid())
			(*(Profiles.begin()))->Attack();
		else 
			Profiles.RemoveFirst(*(Profiles.begin()));
		//auto tmpCharacter = *Profiles.begin();
		//Profiles.RemoveFirst(*(Profiles.begin()));
	}
	//RemoveFromParent();
}

TArray<class AY_Character*>& UY_TimeMark::GetCharacters()
{
	return Profiles.Data;
}
