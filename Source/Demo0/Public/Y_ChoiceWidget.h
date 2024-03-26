// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_ChoiceWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_ChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DescriptionText;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TDelegate<void()>* ChoiceAction;

	UFUNCTION(BlueprintCallable)
	void ExecuteAction();

	UFUNCTION(BlueprintImplementableEvent)
	void ChoiceInit(struct FChoiceStruct& ChoiceInfo);
};
