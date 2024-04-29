// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_ChooseCard.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_ChooseCard : public UUserWidget
{
public:
	GENERATED_BODY()
	TSharedPtr<class Y_ChooseCardInfo> Info;

	TArray<TSharedPtr<class Y_CardInfo>> ChoosedCards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UY_CardW*> CardWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Discribe;

	UFUNCTION(BlueprintImplementableEvent)
	class UY_CardW* CreateShowCard(float RelativePosition);

	UFUNCTION(BlueprintCallable)
	void AfterChoose();

	//传过去该指针，在内部调用该函数。
	UFUNCTION(BlueprintCallable)
	void CardClicked(class UY_CardW* ClickedWidget);

	void LoadInfo(TSharedPtr<class Y_ChooseCardInfo> ToLoadInfo);
};

class DEMO0_API Y_ChooseCardInfo {
public:
	Y_ChooseCardInfo();
	virtual ~Y_ChooseCardInfo();
	UY_ChooseCard* Owner;
	TArray<TSharedPtr<class Y_CardInfo>> Cards;
	int32 ChooseCount;
	bool NeedChooseMax;
	FString ChooseDiscribe;
	virtual void CardClicked(TSharedPtr<class Y_CardInfo> ClickedInfo);

	virtual void AfterChoose(TArray<TSharedPtr<class Y_CardInfo>> ChoosedCards);
};
