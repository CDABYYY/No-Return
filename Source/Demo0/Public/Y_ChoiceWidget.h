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
	class UY_EventWidget* Owner;

	TSharedPtr<class Y_ChoiceInfo> Info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DescriptionText;

	UFUNCTION(BlueprintCallable)
	void ExecuteAction();

	UFUNCTION(BlueprintCallable)
	void Init();
};

class DEMO0_API Y_ChoiceInfo {
public:
	Y_ChoiceInfo();

	virtual ~Y_ChoiceInfo() {};

	class UY_ChoiceWidget* Owner;

	FText Describe;

	virtual FText GetDescribe();

	virtual TSharedPtr<class Y_EventInfo> Execute();
};

class DEMO0_API Y_ChoiceInfoL :public Y_ChoiceInfo {
public:
	TDelegate<void()> Action;

	TSharedPtr<class Y_EventInfo> ToEvent;

	FText Describe;

	template<typename T>
	Y_ChoiceInfoL(FText Description, T&& Lambda, TSharedPtr<class Y_EventInfo> NextEvent = nullptr) {
		Describe = Description;
		Action.BindLambda(Lambda);
		ToEvent = NextEvent;
	}
	virtual FText GetDescribe()override {
		return Describe;
	}

	virtual TSharedPtr<class Y_EventInfo> Execute()override {
		Action.ExecuteIfBound();
		return ToEvent;
	}
};


class DEMO0_API Y_ChoiceInfoLR :public Y_ChoiceInfo {
public:
	TDelegate<TSharedPtr<Y_EventInfo>()> Action;

	FText Describe;

	template<typename T>
	Y_ChoiceInfoLR(FText Description, T&& Lambda) {
		Describe = Description;
		Action.BindLambda(Lambda);
	}
	virtual FText GetDescribe()override {
		return Describe;
	}

	virtual TSharedPtr<class Y_EventInfo> Execute()override {
		return Action.Execute();
	}
};
