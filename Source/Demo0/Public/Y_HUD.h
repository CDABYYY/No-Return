// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_GameInstance.h"
#include "Y_HUD.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_HUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UY_GameInstance* YGameInstance;

	UFUNCTION(BlueprintCallable)
	void NoticeMessage(FString message, int color = 0);

	UFUNCTION(BlueprintCallable)
	void HUDInit();

	UFUNCTION(BlueprintCallable)
	float GetProcess();
};
