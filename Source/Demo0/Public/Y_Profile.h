// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_Profile.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_Profile : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AY_Character* Character;

	float* RunTime;

	int32* AttackTime;

	UFUNCTION(BlueprintCallable)
	int GetRelativePosition();

	UFUNCTION(BlueprintCallable)
	void ProfileInit(class AY_Character* ReadCharacter);
};
