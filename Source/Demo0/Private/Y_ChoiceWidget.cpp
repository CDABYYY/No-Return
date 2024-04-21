// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_ChoiceWidget.h"
#include "Y_EventWidget.h"

void UY_ChoiceWidget::ExecuteAction()
{
	auto PE = Info->Execute();
	if (PE == nullptr) {
		Owner->PullEvent(true);
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

}

FText Y_ChoiceInfo::GetDescribe()
{
	return FText::FromString(TEXT("UnNamed"));
}

TSharedPtr<class Y_EventInfo> Y_ChoiceInfo::Execute()
{
	return nullptr;
}
