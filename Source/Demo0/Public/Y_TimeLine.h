// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_TimeLine.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_TimeLine : public UUserWidget
{
	GENERATED_BODY()
public:
	static UY_TimeLine* YTimeLine;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UY_GameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<class AY_Character*, class UY_Profile*> CP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class UY_Profile> Profileclass;

	UFUNCTION(BlueprintCallable)
	void TimeLineInit();

	UFUNCTION(BlueprintImplementableEvent)
	void AddCharacterProfile(class AY_Character* ReadCharacter);
};
