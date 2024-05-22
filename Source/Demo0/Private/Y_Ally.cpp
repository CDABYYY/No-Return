// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Ally.h"
#include "Y.h"
#include "Y_GameInstance.h"
#include "CameraPawn.h"
#include "Y_PlayerController.h"

AY_Ally::AY_Ally() {

	CharacterPriority = 1;
	CharacterAttackTime = 0;
	MaxHealth = 100;
	Health = 100;
	Shield = 0;
	CharacterStatus = 0;

	CharacterID = 0;
	UsingPicture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Resource/CharacterPictures/0.0'"));
}

void AY_Ally::BeginPlay()
{
	Super::BeginPlay();
	Y::GetGameInstance()->MainCharacter = this;
}

void AY_Ally::Attack() {
	Y::GetPlayer()->ClickAble = true;
}

void AY_Ally::Injured() {
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("MC Injured"));
}

void AY_Ally::CharacterDead()
{
	Y::GetPlayer()->ClickAble = true;
	Y::GetController()->ShowDeadWidget();
}
