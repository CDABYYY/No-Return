// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_Trophy.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_Trophy : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Clicked();

	UFUNCTION(BlueprintCallable)
	void Init();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* UsingPicture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TrophyDescribe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TrophyAmount;

	TSharedPtr<class Y_TrophyInfo> Info;
};

class DEMO0_API Y_TrophyInfo 
{
public:
	int32 Counts;
	virtual UTexture2D* Picture();
	virtual FText Describe();
	virtual FText Amount();
	virtual void Clicked();
};