// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_BuffIcon.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_BuffIcon : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 BuffCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuffID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BuffPicture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText BuffDescribe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText BuffName;

	TSharedPtr<class Y_Buff> Buff;

	UFUNCTION(BlueprintCallable)
	void Update();

	UFUNCTION(BlueprintImplementableEvent)
	void SetLocation(int32 Line, int32 Column);
};
