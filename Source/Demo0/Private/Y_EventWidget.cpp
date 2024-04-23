// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_EventWidget.h"
#include "Y_ChoiceWidget.h"

void UY_EventWidget::EventInit()
{
	EventPicture = Info->GetPicture();
	EventDescription = Info->GetDescription();
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
	Description = FText::FromString(TEXT("UnNamed"));
}

FText Y_EventInfo::GetDescription()
{
	return Description;
}

UTexture2D* Y_EventInfo::GetPicture()
{
	return Picture;
}


void Y_EventInfo::EndEvent()
{
}
