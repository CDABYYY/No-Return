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

	TSharedPtr<class Y_EventInfo> Info;

	UFUNCTION(BlueprintCallable)
	void EventInit();

	UFUNCTION(BlueprintImplementableEvent)
	class UY_ChoiceWidget* CreateChoiceUI();

	UFUNCTION(BlueprintImplementableEvent)
	void PullEvent(bool Reverse);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText EventDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* EventPicture;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<class UY_ChoiceWidget*> ChoiceWidgets;

	void LoadInfo(TSharedPtr<class Y_EventInfo> LoadingInfo);
};

class DEMO0_API Y_EventInfo {
public:
	Y_EventInfo();

	virtual ~Y_EventInfo() {};

	class UY_EventWidget* Owner;

	FText EventDescription();

	UTexture2D* Picture();

	TArray<TSharedPtr<class Y_ChoiceInfo>> Choices;

	virtual void EndEvent();
};