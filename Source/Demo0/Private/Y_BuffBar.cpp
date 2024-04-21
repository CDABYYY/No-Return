// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_BuffBar.h"
#include "Y_Character.h"
#include "Y_StatusBar.h"
#include "Y_BuffIcon.h"

void UY_BuffBar::Update()
{
	int32 i = 0;
	Y::Log(0, TEXT("Buff Count: %d"), Owner->Buffs->Buff.Num());
	for (auto& p : Owner->Buffs->Buff) {
		if (p->Living && p->ShowAble) {
			if (!IsValid(p->IconWidget)) {
				auto PW = NewBuffIcon();
				PW->Buff = p;
				p->IconWidget = PW;
				PW->Update();
				PW->SetLocation(i / 5, i % 5);
			}
			else {
				p->IconWidget->Update();
				p->IconWidget->SetLocation(i / 5, i % 5);
			}
			i++;
		}
	}
}
