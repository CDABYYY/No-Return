// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_CardH.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_CardH : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void Update();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<class UY_CardW* >Cards;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UY_CardW* ChoosedCard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Pressing;

	UFUNCTION(BlueprintCallable)
	void RemoveCard(class UY_CardW* ToRemoveCard);

	UFUNCTION(BlueprintCallable)
	void Clear();

	void AddCard(TSharedPtr<class Y_CardInfo> Card);

	UFUNCTION(BlueprintImplementableEvent)
	class UY_CardW* CreateCard();

	UFUNCTION(BlueprintCallable)
	void TestAdd();
};
