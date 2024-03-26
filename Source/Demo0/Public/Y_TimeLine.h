// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YOArray.h"
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

	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	YOArray<class UY_TimeMark*>TimeMarks;

	UFUNCTION(BlueprintCallable)
	void TimeLineInit();

	UFUNCTION(BlueprintCallable)
	void AddCharacter(class AY_Character* AddedCharacter);

	UFUNCTION(BlueprintCallable)
	void RemoveCharacter(class AY_Character* RemovedCharacter);

	UFUNCTION(BlueprintCallable)
	void UpdateTimeMark();

	UFUNCTION(BlueprintImplementableEvent)
	class UY_TimeMark* NewTimeMark();

	UFUNCTION(BlueprintImplementableEvent)
	void AddCharacterProfile(class AY_Character* ReadCharacter);
};
