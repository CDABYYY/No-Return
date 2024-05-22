// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_EventWidget.h"
#include "Y_ChoiceWidget.h"
#include "Y.h"
#include "Y_Fighting.h"
#include "Y_RoomWidget.h"

void UY_EventWidget::EventInit()
{
	EventPicture = Info->GetPicture();
	EventDescription = Info->GetDescription();
	for (auto& s:Info->Choices)
	{
		auto PC = CreateChoiceUI();
		PC->Info = s;
		PC->Owner = this;
		PC->Init();
		ChoiceWidgets.Add(PC);
	}
}

void UY_EventWidget::LoadInfo(TSharedPtr<class Y_EventInfo> LoadingInfo)
{
	for (auto& p : ChoiceWidgets) {
		if(IsValid(p))
			p->RemoveFromParent();
	}
	ChoiceWidgets.Empty();
	if (LoadingInfo != nullptr) {
		Info = LoadingInfo;
		EventInit();
	}
}

Y_EventInfo::Y_EventInfo()
{
	Description = FText::FromString(TEXT("UnNamed"));
}

void Y_EventInfo::BindMessage(int32 ID)
{
	FString Name = FString::Printf(TEXT("%d"), ID);
	FString Path = TEXT("/Script/Engine.Texture2D'/Game/Resource/EventPictures/");
	Path.Append(Name);
	Path.Append(TEXT("."));
	Path.Append(Name);
	Path.Append(TEXT("'"));
	auto P = LoadObject<UTexture2D>(nullptr, Path.GetCharArray().GetData());
	if (IsValid(P))Picture = P;
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
