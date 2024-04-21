// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_Settle.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_Settle : public UUserWidget
{
	GENERATED_BODY()
public:
	TSharedPtr<class Y_SettleInfo> Info;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText Tittle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<class UY_Trophy*> Trophys;

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintImplementableEvent)
	class UY_Trophy* CreateTrophy();

	UFUNCTION(BlueprintCallable)
	void EndWork();
};

class DEMO0_API Y_SettleInfo 
{
public:
	virtual ~Y_SettleInfo() {};

	virtual FText Describe();

	virtual void EndWork();

	TArray< TSharedPtr<class Y_TrophyInfo> > TrophyInfos;
};