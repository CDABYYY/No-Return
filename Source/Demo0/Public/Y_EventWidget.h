// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_EventWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_EventWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void EventInit();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString EventDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ChoiceName;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<TDelegate<void()>> ChoiceAction;
};
