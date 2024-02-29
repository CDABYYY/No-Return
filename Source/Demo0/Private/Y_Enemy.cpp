// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Enemy.h"
#include "Y.h"
#include "Y_Floor.h"

AY_Enemy::AY_Enemy()
{
	CharacterPriority = 0;
	CharacterAttackTime = 0;
	MaxHealth = 100;
	Health = 100;
	Shield = 0;
	CharacterStatus = 0;
}

void AY_Enemy::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Character Attack"));
	ReadyAttack.ExecuteIfBound();
	ReadyAttack.Unbind();
	int32 distance = abs(StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber);
	if (distance <= 1) {
		ReadyAttack.BindUObject(this, &AY_Enemy::ShortAttack);
	}
	else if (distance <= 2) {
		ReadyAttack.BindUObject(this, &AY_Enemy::HardAttack);
	}
	else ReadyAttack.BindUObject(this, &AY_Enemy::MoveMotion);
}

void AY_Enemy::Injured()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Character Injured!"));
}

void AY_Enemy::ShortAttack()
{
	MyPlayMontage(TEXT("Attack1"), StandFloor, 1, false);
}

void AY_Enemy::HardAttack()
{
	MyPlayMontage(TEXT("Attack2"), StandFloor, 1, false);
}

void AY_Enemy::MoveMotion()
{
	int32 direction = 1;
	if (StandFloor->SerialNumber > Y::GetMainCharacter()->StandFloor->SerialNumber)
		direction = -1;
	MyPlayMontage(TEXT("Move1"), Y::GetFloors()[StandFloor->SerialNumber + direction], 1, true);
	StandFloor = Y::GetFloors()[StandFloor->SerialNumber + direction];
}
