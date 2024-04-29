// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

//USTRUCT(BlueprintType)
//struct FAtomLog 
//{
//	GENERATED_USTRUCT_BODY()
//
//	//FAtomLog() {};
//
//	//FAtomLog(int32 ID, int32 Count, FText Description) :BuffID(ID), LevelCount(Count), BuffDescription(Description) {};
//
//	UPROPERTY(EditAnywhere,BlueprintReadWrite)
//	int32 BuffID;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 LevelCount;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText BuffDescription;
//};
//
//
//
//USTRUCT(BlueprintType)
//struct FBuffLog
//{
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY(EditAnywhere,BlueprintReadWrite)
//	int32 LogType;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 LogID;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 Cost;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText LogDescription;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class AY_Character* FromCharacter;
//
//	//class Y_EnemyInfo* FromCharacter;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class AY_Character* ToCharacter;
//
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<TSharedPtr<class Y_Buff>> ExecuteBuffs;
//
//	//TArray<FAtomLog*>ExecuteBuffs;
//
//	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
//	TArray<TSharedPtr<class Y_Buff>> InfluentBuffs;
//
//	void LogInit(class AY_Character* FC, class AY_Character* TC) {
//		FromCharacter = FC;
//		ToCharacter = TC;
//	}
//
//	//Didn't Added To Use.
//	static TArray<FBuffLog> FightLogs;
//	static FBuffLog WritingLog;
//};



class DEMO0_API Y_Buff: public TSharedFromThis<Y_Buff>
{

	//Called that only Normal Pointer which is turned by SharedPtr can use AsShared()
	//Because Only after MakeShareable() It's WeakPtr can be Init.

public:
	Y_Buff();
	Y_Buff(int32 i) :BuffCount(i){};
	Y_Buff(int32 Condition, bool ToGet) :TriggerCondition(Condition) {};

	virtual void Init(int32 BuffCount);
	virtual ~Y_Buff();
	
	FText BuffName;
	
	int32 BuffLevel;//Whether it can be cleared
	
	int32 BuffCount;
	
	int32 BuffAsType;

	int32 BuffID;
	
	int32 BuffOrder;//Deside the Order which buff execute. Smaller Order will execute earlier.
	
	class AY_Character* OwnerCharacter;

	int32 BuffProperty;//Buff belong to Damage(1),Move(2),Buff(3),Mark(4)

	TSet<int32> BuffExtend;

	FString CountName;//Temporary Abandoned.

	int32 TriggerCondition;//When the Buff Execute.

	bool Addable;//For Normal Buffs

	//Waring:: Avoid Remove Buff From Character. Just Make It UnLiving.
	bool Living;//If Buff Can Execute And Show;

	bool ShowAble;
	
	FText BuffDescribe;

	UTexture2D* BuffPicture;

	class UY_BuffIcon* IconWidget;

	virtual FText GetDescribe();

	virtual UTexture2D* GetPicture();

	enum : int32
	{
		//Begin Action
		BeginAction = (1 << 1),
		//Begin Attack
		BeginAttack = (1 << 2),
		//Begin Injured
		BeginInjured = (1 << 3),
		//Injuring
		Injuring = (1 << 4),
		//After Injured
		AfterInjured = (1 << 5),
		//After Attack
		AfterAttack = (1 << 6),
		//Begin Move
		BeginMove = (1 << 7),
		//Begin Moved
		BeginMoved = (1 << 8),
		//Moving
		Moving = (1 << 9),
		//After Moved
		AfterMoved = (1 << 10),
		//After Move
		AfterMove = (1 << 11),
		//Begin Buff
		BeginBuff = (1 << 12),
		//Begin Buffed
		BeginBuffed = (1 << 13),
		//Buffing
		Buffing = (1 << 14),
		//After Buffed
		AfterBuffed = (1 << 15),
		//After Buff
		AfterBuff = (1 << 16),
		//After Action
		AfterAction = (1 << 17),
		//Death Detect
		DetectDeath = (1 << 18),
		//Begin Death
		BeginDeath = (1 << 19),
		//After Death
		AfterDeath = (1 << 20),
		//Begin Tick
		BeginTick = (1 << 21),
		//Ticking
		Ticking = (1 << 22),
		//After Tick
		AfterTick = (1 << 23),
		//Kill Event
		AfterKill = (1 << 24),
		//Reversed Events , The first Buff of ToBuff will show its Type 
		ReversedEvent = (1 << 25),
		//Begin Fight
		BeginFight = (1 << 26),
		//After Fight
		AfterFight = (1 << 27),
		//Character Spawn
		CharacterSpawn = (1 << 28),
	};

	//Return Without 0 will end Following Execute				
	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs,int32 ExecuteCondition,FString TriggerAction, bool TryAttack = false);

	virtual FText printBuff(bool PrintLog = false)const;
	virtual void AddBuff(Y_Buff* OtherBuff);
	virtual void ReplaceBuff(Y_Buff* OtherBuff);
	//Need Rewrite : Add Param bool to be called by Y::ExecuteAction
	virtual void AddToCharacter(class AY_Character* TargetCharacter,bool Execute);//Buff will Added To Character Defaultly. Part For Special Effects.
	virtual void RemoveFromCharacter();//Generally For Special Effects. Warning:This Fuction Will Generally Kill Self! If You Need Call it Safely, you should keep a TSharedPtr.
	virtual bool AcceptBuffAdd(Y_Buff* OtherBuff);
	virtual FString PrinCount();

	void AddInExecuteLog();
	void AddInInfluentLog();
};

class DEMO0_API Y_BuffL :public Y_Buff {
public:
	TDelegate<int32()> ToExecute;

	Y_BuffL(int32 ExecuteCondition, TDelegate<int32()> ToBind) : ToExecute(ToBind) { TriggerCondition = ExecuteCondition; };

	template<typename Fun>
	Y_BuffL(int32 ExecuteCondition, Fun&& lambda) { ToExecute.BindLambda(lambda); TriggerCondition = ExecuteCondition; }

	template<typename Fun>
	Y_BuffL(int32 ExecuteCondition, int32 Order, Fun&& lambda) { ToExecute.BindLambda(Forward(lambda)); TriggerCondition = ExecuteCondition; BuffOrder = Order; }

	//template<typename Fun, typename...Vals>
	//Y_BuffL(int32 ExecuteCondition, Fun*&& ObjectPtr, Vals&&... vals) : { ToExecute.BindUObject(Forward(ObjectPtr), Forward(vals...)); TriggerCondition = ExecuteCondition; }

	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;

};

class DEMO0_API Y_BuffR :public Y_Buff {
public:
	class Y_RoomInfo* BindedWidget;
	Y_BuffR(class Y_RoomInfo* BindWidget);

	virtual int32 execute(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition, FString TriggerAction, bool TryAttack = false)override;
};

class DEMO0_API CardBuff :public Y_Buff {
public:
	TSharedPtr<class Y_CardInfo> CardInfo;
	CardBuff(TSharedPtr<class Y_CardInfo> Card);
	virtual void AddToCharacter(class AY_Character* TargetCharacter,bool Execute)override;
};


class DEMO0_API ActionBuff :public Y_Buff {
public:
	TSharedPtr<class Y_CharacterAction> ActionInfo;
	ActionBuff(TSharedPtr<class Y_CharacterAction> Action);
	virtual void AddToCharacter(class AY_Character* TargetCharacter,bool Execute)override;
};