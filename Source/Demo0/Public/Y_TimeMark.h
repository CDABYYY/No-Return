// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YOArray.h"
#include "Blueprint/UserWidget.h"
#include "Y_TimeMark.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_TimeMark : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ExecuteTime;

	UFUNCTION(BlueprintCallable)
	float GetRelativePosition();

	UFUNCTION(BlueprintCallable)
	void TimeMarkInit();

	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	YOArray<class AY_Character*> Profiles;

	UFUNCTION(BlueprintCallable)
	void AddProfile(class AY_Character* ProfileAdded);

	UFUNCTION(BlueprintCallable)
	void RemoveProfile(class AY_Character* ProfileRemoved);

	UFUNCTION(BlueprintCallable)
	virtual void ExecuteMark();

	UFUNCTION(BlueprintCallable)
	TArray<class AY_Character*>& GetCharacters();
};
