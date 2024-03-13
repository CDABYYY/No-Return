// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_RoomWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_RoomWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	static UY_RoomWidget* CurrentRoom;

	UFUNCTION(BlueprintCallable)
	virtual void RoomInit();


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
