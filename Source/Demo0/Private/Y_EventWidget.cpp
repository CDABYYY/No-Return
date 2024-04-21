// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_EventWidget.h"
#include "Y_ChoiceWidget.h"

void UY_EventWidget::EventInit()
{
	EventPicture = Info->Picture();
	EventDescription = Info->EventDescription();
	for (auto& s:Info->Choices)
	{
		auto PC = CreateChoiceUI();
		PC->Info = s;
		PC->Init();
		ChoiceWidgets.Add(PC);
	}
}

void UY_EventWidget::LoadInfo(TSharedPtr<class Y_EventInfo> LoadingInfo)
{
	for (auto& p : ChoiceWidgets) {
		p->RemoveFromParent();
	}
	if (LoadingInfo != nullptr) {
		Info = LoadingInfo;
		EventInit();
	}
}

Y_EventInfo::Y_EventInfo()
{
}

FText Y_EventInfo::EventDescription()
{
	return FText();
}

UTexture2D* Y_EventInfo::Picture()
{
	return nullptr;
}

void Y_EventInfo::EndEvent()
{
}
