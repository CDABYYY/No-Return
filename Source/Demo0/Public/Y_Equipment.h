// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Y_Buff.h"
/**
 * 
 */
class DEMO0_API Y_Equipment:public TSharedFromThis<class Y_Equipment>
{
public:
	Y_Equipment();
	virtual ~Y_Equipment();
	int32 EquipmentID;
	int32 SkillCD;
	int32 NowCD;
	int32 CanUseCount;
	int32 GetPrice();
	FText EquipmentName;
	UTexture2D* UsingPicture;
	int32 PressingStatus;
	TSharedPtr<class Y_Equipment> FromEquipment;
	bool UseAble;
	bool NeedTarget;
	float DrawWeight;
	int32 CostMoney;
	int32 EquipLevel;
	class UY_EquipmentW* Owner;

	TSharedPtr<class Y_Buff> AddedBuff;

	virtual void CanUsed();

	virtual void Update();
	virtual void BeginFighting();
	virtual void Play(bool Execute);
	virtual void Equiped();
	//TSharedPtr<Y_Buff> AddInFight();
	virtual void UnEquiped();

	virtual class AY_Character* GetOwner();

	static void DrawCard(int32 DrawCount, bool Execute);

	virtual void Clicked();

	virtual void ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ExecuteBuffs, bool TryExecute);

	virtual bool AcceptFloor(class AY_Floor* GetFloor);

	virtual float GetWeight();

	virtual TArray<TSharedPtr<class Y_Equipment>> Upgrade();
};
