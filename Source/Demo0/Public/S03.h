// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#include "Y_EnemyInfo.h"

void LS03();

class DEMO0_API cateran1 : public Y_EnemyInfo
{
public:
	cateran1();
};

class DEMO0_API cateran2 : public Y_EnemyInfo
{
public:
	cateran2();
};

class DEMO0_API cateran3 : public Y_EnemyInfo
{
public:
	cateran3();
};

class DEMO0_API militia1 : public Y_EnemyInfo
{
public:
	militia1();
};

class DEMO0_API militia2 : public Y_EnemyInfo
{
public:
	militia2();
};

class DEMO0_API militia3 : public Y_EnemyInfo
{
public:
	militia3();
};

class DEMO0_API disciple1 : public Y_EnemyInfo
{
public:
	disciple1();
};

class DEMO0_API disciple2 : public Y_EnemyInfo
{
public:
	disciple2();
};

class DEMO0_API disciple3 : public Y_EnemyInfo
{
public:
	disciple3();
};

class DEMO0_API sifu : public Y_EnemyInfo
{
public:
	sifu();
};

class DEMO0_API droog1 : public Y_EnemyInfo
{
public:
	droog1();
};

class DEMO0_API droog2 : public Y_EnemyInfo
{
public:
	droog2();
};

class DEMO0_API droog3 : public Y_EnemyInfo
{
public:
	droog3();
};

class DEMO0_API guard1 : public Y_EnemyInfo
{
public:
	guard1();
};

class DEMO0_API guard2 : public Y_EnemyInfo
{
public:
	guard2();
};

class DEMO0_API guard3 : public Y_EnemyInfo
{
public:
	guard3();
};

class DEMO0_API challenger1 : public Y_EnemyInfo
{
public:
	challenger1();
	virtual void EnemyDead()override;
};

class DEMO0_API challenger2 : public Y_EnemyInfo
{
public:
	challenger2();
	virtual void EnemyDead()override;
};

class DEMO0_API challenger3 : public Y_EnemyInfo
{
public:
	challenger3();
	virtual void EnemyDead()override;
};

class DEMO0_API champion : public Y_EnemyInfo
{
public:
	champion();
};

class DEMO0_API invader1 : public Y_EnemyInfo
{
public:
	invader1();
	virtual void LoadCharacter(AY_Character* Owner)override;
};

class DEMO0_API invader2 : public Y_EnemyInfo
{
public:
	invader2();
	virtual void LoadCharacter(AY_Character* Owner)override;
};

class DEMO0_API invader3 : public Y_EnemyInfo
{
public:
	invader3();
	virtual void LoadCharacter(AY_Character* Owner)override;
};

class DEMO0_API army1 : public Y_EnemyInfo
{
public:
	army1();
};

class DEMO0_API army2 : public Y_EnemyInfo
{
public:
	army2();
};

class DEMO0_API army3 : public Y_EnemyInfo
{
public:
	army3();
};

class DEMO0_API lifeguard1 : public Y_EnemyInfo
{
public:
	lifeguard1();
};

class DEMO0_API lifeguard2 : public Y_EnemyInfo
{
public:
	lifeguard2();
};

class DEMO0_API lifeguard3 : public Y_EnemyInfo
{
public:
	lifeguard3();
};




