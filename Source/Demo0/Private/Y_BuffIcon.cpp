// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_BuffIcon.h"
#include "Y_Buff.h"

void UY_BuffIcon::Update()
{
	BuffCount = Buff->BuffCount;
	BuffName = Buff->BuffName;
	BuffID = Buff->BuffID;
	BuffDescribe = Buff->GetDescribe();
	BuffPicture = Buff->GetPicture();
}
