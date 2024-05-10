// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_RoomWidget.generated.h"

/**
 * 
 */
class DEMO0_API Y_RoomInfo
{
public:

	bool Arriveable;

	//To Cooperate Buff.
	int32 NeedKills = 0;

	int32 RoomID;

	int32 EndEventType;

	//1:Leave 2:Fight 3:EndRoom
	void ChangeEndType(int32 ChangedValue);

	UTexture2D* UsingTexture;

	class UY_RoomWidget* Owner;

	virtual FText GetDescribe();

	virtual void SetArrivable();

	virtual bool IsArrivable();

	virtual void Passed();

	//return nullptr if this room will execute
	virtual TSharedPtr<Y_RoomInfo> RoomClicked();

	virtual void LeaveRoom();

	virtual float GetWeight();

	void EndEvent();

	void DoToEndRoom();

	static void GetNewCard();

	static void DeleteCard();

	static TSharedPtr<class Y_EventInfo> DeleteRandomCard(int32 Count = 3);

	static TSharedPtr<class Y_EventInfo> UpgradeEquipment(int32 Level,int32 Count = 3);
};




UCLASS()
class DEMO0_API UY_RoomWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	static UY_RoomWidget* CurrentRoom;

	//0: Can In, 1: Can't In, 2: Entered, 3: Passed
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 RoomStatus;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* UsingTexture;

	TSharedPtr<Y_RoomInfo> Info;

	virtual FText GetDescribe();

	virtual void SetArrivable();

	virtual bool IsArrivable();

	virtual void Passed();

	bool Cleared;

	virtual void LoadInfo(TSharedPtr<class Y_RoomInfo> LoadingInfo);

	UFUNCTION(BlueprintCallable)
	virtual void RoomInit();

	UFUNCTION(BlueprintCallable)
	virtual void RoomClicked();

	UFUNCTION(BlueprintCallable)
	virtual void RoomClosed();

	UFUNCTION(BlueprintCallable)
	virtual void FightBegin();
	UFUNCTION(BlueprintCallable)
	virtual void EventBegin();
	UFUNCTION(BlueprintCallable)
	virtual void FightEnd();
	UFUNCTION(BlueprintCallable)
	virtual void EventEnd();
	UFUNCTION(BlueprintCallable)
	virtual void EventFight();
};


