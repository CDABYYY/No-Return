// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_ChoiceWidget.h"

void UY_ChoiceWidget::ExecuteAction()
{
	ChoiceAction->ExecuteIfBound();
}
