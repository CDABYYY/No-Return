// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_ChoiceWidget.h"
#include "Y_EventWidget.h"
#include "CameraPawn.h"
#include "Y.h"

void UY_ChoiceWidget::ExecuteAction()
{
	auto PE = Info->Execute();
	if (PE == nullptr) {
		Owner->PullEvent(true);
		Y::GetPlayer()->ClickAble = true;
	}
	else {
		Owner->LoadInfo(PE);
	}
}

void UY_ChoiceWidget::Init()
{
	DescriptionText = Info->GetDescribe();
}

Y_ChoiceInfo::Y_ChoiceInfo()
{
	Describe = FText::FromString(TEXT("UnNamed"));
}

FText Y_ChoiceInfo::GetDescribe()
{
	return Describe;
}

TSharedPtr<class Y_EventInfo> Y_ChoiceInfo::Execute()
{
	return nullptr;
}
