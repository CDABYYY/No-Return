// Fill out your copyright notice in the Description page of Project Settings.


#include "S03.h"
#include "Y.h"
#include "S01.h"
#include "Y_ClassBase.h"
#include "Y_Buff.h"
#include "Y_Character.h"
#include "Y_ChoiceWidget.h"

void LS03()
{
	Y::LoadCharacter<cateran1>(1);
	Y::LoadCharacter<cateran2>(2);
	Y::LoadCharacter<cateran3>(3);
	Y::LoadCharacter<militia1>(4);
	Y::LoadCharacter<militia2>(5);
	Y::LoadCharacter<militia3>(6);
	Y::LoadCharacter<disciple1>(7);
	Y::LoadCharacter<disciple2>(8);
	Y::LoadCharacter<disciple3>(9);
	Y::LoadCharacter<sifu>(10);
	Y::LoadCharacter<droog1>(11);
	Y::LoadCharacter<droog2>(12);
	Y::LoadCharacter<droog3>(13);
	Y::LoadCharacter<guard1>(14);
	Y::LoadCharacter<guard2>(15);
	Y::LoadCharacter<guard3>(16);
	Y::LoadCharacter<challenger1>(17);
	Y::LoadCharacter<challenger2>(18);
	Y::LoadCharacter<challenger3>(19);
	Y::LoadCharacter<champion>(20);
	Y::LoadCharacter<invader1>(21);
	Y::LoadCharacter<invader2>(22);
	Y::LoadCharacter<invader3>(23);
	Y::LoadCharacter<army1>(24);
	Y::LoadCharacter<army2>(25);
	Y::LoadCharacter<army3>(26);
	Y::LoadCharacter<lifeguard1>(27);
	Y::LoadCharacter<lifeguard2>(28);
	Y::LoadCharacter<lifeguard3>(29);
}

cateran1::cateran1()
{
	MaxHealth = CurrentHealth = 20;
	BindBlueprint = TEXT("L1P1T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S02>(this));
	Actions.Add(Y::YMakeShared<S03>(this));

	ActionCount = 1;
	EnemyID = 1;
}

cateran2::cateran2()
{
	MaxHealth = CurrentHealth = 15;
	BindBlueprint = TEXT("L1P1T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S04>(this));
	Actions.Add(Y::YMakeShared<S05>(this));

	ActionCount = 1;
	EnemyID = 2;
}

cateran3::cateran3()
{
	MaxHealth = CurrentHealth = 30;
	BindBlueprint = TEXT("L1P1T3");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S06>(this));
	Actions.Add(Y::YMakeShared<S07>(this));

	ActionCount = 1;
	EnemyID = 3;
}

militia1::militia1()
{
	MaxHealth = CurrentHealth = 20;
	BindBlueprint = TEXT("L1P2T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S08>(this));
	Actions.Add(Y::YMakeShared<S09>(this));

	ActionCount = 1;
	EnemyID = 4;
}

militia2::militia2()
{
	MaxHealth = CurrentHealth = 20;
	BindBlueprint = TEXT("L1P2T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S10>(this));
	Actions.Add(Y::YMakeShared<S11>(this));

	ActionCount = 1;
	EnemyID = 5;
}

militia3::militia3()
{
	MaxHealth = CurrentHealth = 40;
	BindBlueprint = TEXT("L1P2T3");
	Actions.Add(Y::YMakeShared<S12>(this));
	Actions.Add(Y::YMakeShared<S13>(this));
	Actions.Add(Y::YMakeShared<S14>(this));

	ActionCount = 1;
	EnemyID = 6;
}

disciple1::disciple1()
{
	MaxHealth = CurrentHealth = 25;
	BindBlueprint = TEXT("L1P3T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S15>(this));
	Actions.Add(Y::YMakeShared<S16>(this));

	ActionCount = 1;
	EnemyID = 7;
}

disciple2::disciple2()
{
	MaxHealth = CurrentHealth = 30;
	BindBlueprint = TEXT("L1P3T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S17>(this));
	Actions.Add(Y::YMakeShared<S18>(this));
	Actions.Add(Y::YMakeShared<S19>(this));

	ActionCount = 1;
	EnemyID = 8;
}

disciple3::disciple3()
{
	MaxHealth = CurrentHealth = 40;
	BindBlueprint = TEXT("L1P3T3");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S20>(this));
	Actions.Add(Y::YMakeShared<S21>(this));
	Actions.Add(Y::YMakeShared<S22>(this));

	ActionCount = 1;
	EnemyID = 9;
}

sifu::sifu()
{
	MaxHealth = CurrentHealth = 90;
	BindBlueprint = TEXT("L1P4");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S23>(this));
	Actions.Add(Y::YMakeShared<S24>(this));
	Actions.Add(Y::YMakeShared<S25>(this));
	Actions.Add(Y::YMakeShared<S26>(this));
	Actions.Add(Y::YMakeShared<S27>(this));
	Actions.Add(Y::YMakeShared<S28>(this));

	ActionCount = 1;
	EnemyID = 10;
}

droog1::droog1()
{
	MaxHealth = CurrentHealth = 30;
	BindBlueprint = TEXT("L2P1T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S29>(this));
	Actions.Add(Y::YMakeShared<S30>(this));

	ActionCount = 1;
	EnemyID = 11;
}

droog2::droog2()
{
	MaxHealth = CurrentHealth = 25;
	BindBlueprint = TEXT("L2P1T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S31>(this));
	Actions.Add(Y::YMakeShared<S32>(this));

	ActionCount = 1;
	EnemyID = 12;
}

droog3::droog3()
{
	MaxHealth = CurrentHealth = 45;
	BindBlueprint = TEXT("L2P1T3");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S33>(this));
	Actions.Add(Y::YMakeShared<S34>(this));
	Actions.Add(Y::YMakeShared<S35>(this));

	ActionCount = 1;
	EnemyID = 13;
}

guard1::guard1()
{
	MaxHealth = CurrentHealth = 35;
	BindBlueprint = TEXT("L2P2T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S36>(this));
	Actions.Add(Y::YMakeShared<S37>(this));

	ActionCount = 1;
	EnemyID = 14;
}

guard2::guard2()
{
	MaxHealth = CurrentHealth = 30;
	BindBlueprint = TEXT("L2P2T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S38>(this));
	Actions.Add(Y::YMakeShared<S39>(this));

	ActionCount = 1;
	EnemyID = 15;
}

guard3::guard3()
{
	MaxHealth = CurrentHealth = 50;
	BindBlueprint = TEXT("L2P2T3");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S40>(this));
	Actions.Add(Y::YMakeShared<S41>(this));
	Actions.Add(Y::YMakeShared<S42>(this));

	ActionCount = 1;
	EnemyID = 16;
}

challenger1::challenger1()
{
	MaxHealth = CurrentHealth = 40;
	BindBlueprint = TEXT("L2P3T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S43>(this));
	Actions.Add(Y::YMakeShared<S44>(this));

	ActionCount = 1;
	EnemyID = 17;
}

void challenger1::EnemyDead()
{
	Y_StatusBar S1{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(Owner, Y::GetMainCharacter(), S1);
}

challenger2::challenger2()
{
	MaxHealth = CurrentHealth = 30;
	BindBlueprint = TEXT("L2P3T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S45>(this));
	Actions.Add(Y::YMakeShared<S46>(this));
	Actions.Add(Y::YMakeShared<S47>(this));

	ActionCount = 1;
	EnemyID = 18;
}

void challenger2::EnemyDead()
{
	Y_StatusBar S1{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(Owner, Y::GetMainCharacter(), S1);
}

challenger3::challenger3()
{
	MaxHealth = CurrentHealth = 60;
	BindBlueprint = TEXT("L2P3T3");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S48>(this));
	Actions.Add(Y::YMakeShared<S49>(this));
	Actions.Add(Y::YMakeShared<S50>(this));
	Actions.Add(Y::YMakeShared<S51>(this));

	ActionCount = 1;
	EnemyID = 19;
}

void challenger3::EnemyDead()
{
	Y_StatusBar S1{ Y::YMakeShared<ExposeBuff>(2) };
	ExecuteAction(Owner, Y::GetMainCharacter(), S1);
}

champion::champion()
{
	MaxHealth = CurrentHealth = 150;
	BindBlueprint = TEXT("L2P4");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S52>(this));
	Actions.Add(Y::YMakeShared<S53>(this));
	Actions.Add(Y::YMakeShared<S54>(this));
	Actions.Add(Y::YMakeShared<S55>(this));

	ActionCount = 1;
	EnemyID = 20;
}

invader1::invader1()
{
	MaxHealth = CurrentHealth = 60;
	BindBlueprint = TEXT("L3P1T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S56>(this));
	Actions.Add(Y::YMakeShared<S57>(this));

	ActionCount = 1;
	EnemyID = 21;
}

void invader1::LoadCharacter(AY_Character* NewOwner)
{
	Y_StatusBar S1{ Y::YMakeShared<MoraleBuff>(5) };
	ExecuteAction(nullptr, NewOwner, S1);
}

invader2::invader2()
{
	MaxHealth = CurrentHealth = 50;
	BindBlueprint = TEXT("L3P1T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S58>(this));
	Actions.Add(Y::YMakeShared<S59>(this));
	Actions.Add(Y::YMakeShared<S60>(this));

	ActionCount = 1;
	EnemyID = 22;
}

void invader2::LoadCharacter(AY_Character* NewOwner)
{
	Y_StatusBar S1{ Y::YMakeShared<MoraleBuff>(5) };
	ExecuteAction(nullptr, NewOwner, S1);
}

invader3::invader3()
{
	MaxHealth = CurrentHealth = 100;
	BindBlueprint = TEXT("L3P1T3");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S61>(this));
	Actions.Add(Y::YMakeShared<S62>(this));
	Actions.Add(Y::YMakeShared<S63>(this));

	ActionCount = 1;
	EnemyID = 23;
}

void invader3::LoadCharacter(AY_Character* NewOwner)
{
	Y_StatusBar S1{ Y::YMakeShared<MoraleBuff>(5) };
	ExecuteAction(nullptr, NewOwner, S1);
}

army1::army1()
{
	MaxHealth = CurrentHealth = 70;
	BindBlueprint = TEXT("L3P2T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S64>(this));
	Actions.Add(Y::YMakeShared<S65>(this));
	Actions.Add(Y::YMakeShared<S66>(this));

	ActionCount = 1;
	EnemyID = 24;
}

army2::army2()
{
	MaxHealth = CurrentHealth = 55;
	BindBlueprint = TEXT("L3P2T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S67>(this));
	Actions.Add(Y::YMakeShared<S68>(this));
	Actions.Add(Y::YMakeShared<S69>(this));

	ActionCount = 1;
	EnemyID = 25;
}

army3::army3()
{
	MaxHealth = CurrentHealth = 100;
	BindBlueprint = TEXT("L3P2T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S70>(this));
	Actions.Add(Y::YMakeShared<S71>(this));
	Actions.Add(Y::YMakeShared<S72>(this));

	ActionCount = 1;
	EnemyID = 26;
}

lifeguard1::lifeguard1()
{
	MaxHealth = CurrentHealth = 100;
	BindBlueprint = TEXT("L3P3T1");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S73>(this));
	Actions.Add(Y::YMakeShared<S74>(this));

	ActionCount = 1;
	EnemyID = 27;
}

lifeguard2::lifeguard2()
{
	MaxHealth = CurrentHealth = 60;
	BindBlueprint = TEXT("L3P3T2");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S75>(this));
	Actions.Add(Y::YMakeShared<S76>(this));
	Actions.Add(Y::YMakeShared<S77>(this));

	ActionCount = 1;
	EnemyID = 28;
}

lifeguard3::lifeguard3()
{
	MaxHealth = CurrentHealth = 120;
	BindBlueprint = TEXT("L3P3T3");
	Actions.Add(Y::YMakeShared<S01>(this));
	Actions.Add(Y::YMakeShared<S78>(this));
	Actions.Add(Y::YMakeShared<S79>(this));
	Actions.Add(Y::YMakeShared<S80>(this));
	Actions.Add(Y::YMakeShared<S81>(this));

	ActionCount = 1;
	EnemyID = 29;
}

