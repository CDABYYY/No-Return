// Fill out your copyright notice in the Description page of Project Settings.


#include "Y_Enemy.h"
#include "Y.h"
#include "Y_Floor.h"
#include "Y_GameInstance.h"
#include "Y.h"
#include "Y_StatusBar.h"
#include "Y_EnemyInfo.h"

AY_Enemy::AY_Enemy()
{
	CharacterPriority = 0;
	CharacterAttackTime = 0;
	MaxHealth = 20;
	Health = 20;
	Shield = 0;
	CharacterStatus = 0;

	CharacterID = (1 << 10);
}

void AY_Enemy::Attack()
{
	Info->EnemyAttack();
	//Y::GetGameInstance()->AddAtk(this);
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Character Attack"));
	//UE_LOG(LogTemp, Warning, TEXT("Enemy Attack"));
	//ReadyAttack.ExecuteIfBound();
	//ReadyAttack.Unbind();
	//ExecuteAction(this, nullptr, *Buffs, Y_Buff::AfterAction, TEXT("After Action"));

	//if(ExecuteAction(this,nullptr,*Buffs,Y_Buff::BeginAction,TEXT("Begin Action")) == 0)
	//{
	//	int32 distance = abs(StandFloor->SerialNumber - Y::GetMainCharacter()->StandFloor->SerialNumber);
	//	if (distance <= 1) {
	//		ReadyAttack.BindUObject(this, &AY_Enemy::ShortAttack);
	//		CharacterAttackTime += 20;
	//		Y::GetGameInstance()->AddAtk(this);
	//	}
	//	else if (distance <= 2) {
	//		ReadyAttack.BindUObject(this, &AY_Enemy::HardAttack);
	//		CharacterAttackTime += 40;
	//		Y::GetGameInstance()->AddAtk(this);
	//	}
	//	else {
	//		ReadyAttack.BindUObject(this, &AY_Enemy::MoveMotion);
	//		CharacterAttackTime += 15;
	//		Y::GetGameInstance()->AddAtk(this);
	//	}
	//}
}

void AY_Enemy::Injured()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Character Injured!"));
}

void AY_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

void AY_Enemy::ShortAttack()
{
	MyPlayMontage(TEXT("Attack1"), StandFloor, 1, false);
	AY_Character* ToCharacter = nullptr;
	ToCharacter = Y::GetFloors()[StandFloor->SerialNumber - 1]->StandCharacter;
	if (IsValid(ToCharacter)) {
		Y_StatusBar ToBuff;
		Y_Buff* HealthBuff = new Y_Buff();
		HealthBuff->BuffCount = 10;
		ToBuff.AddBuff(HealthBuff);
		Y::ExecuteAction(this, ToCharacter, ToBuff, TEXT("ShortAttack"));
	}
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
	CharacterLogicalMove(Y::GetFloors()[StandFloor->SerialNumber + direction]);
}

void AY_Enemy::CharacterDead()
{
	//UE_LOG(LogTemp, Warning, TEXT("Enemy Dead"));
	//MyPlayMontage(TEXT("Dead"), StandFloor, 0.2, false);
	Info->EnemyDead();
}
