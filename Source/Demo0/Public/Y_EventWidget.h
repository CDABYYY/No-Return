// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_EventWidget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FChoiceStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString DescriptionText;

	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TDelegate<void()> ChoiceAction;
};
			



UCLASS()
class DEMO0_API UY_EventWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void EventInit();

	UFUNCTION(BlueprintImplementableEvent)
	UUserWidget* CreateChoiceUI(FChoiceStruct& ChoiceI1nfo);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString EventDescription;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UUserWidget*> ChoiceWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChoiceStruct> ChoiceAction;
};
