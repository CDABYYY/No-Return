// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_EventWidget.h"

void UY_EventWidget::EventInit()
{
	for (auto& s:ChoiceAction)
	{
		ChoiceWidgets.Add(CreateChoiceUI(s));
	}
}
