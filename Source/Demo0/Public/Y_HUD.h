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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UY_TimeLine* TimeLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UY_EquipmentH* EquipmentWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText FlowingMessage;

	void FlowMessage(FText NewMessage, int32 color);

	UFUNCTION(BlueprintImplementableEvent)
	void NoticeMessage(FName message, int32 color);

	UFUNCTION(BlueprintCallable)
	void HUDInit();

	UFUNCTION(BlueprintCallable)
	float GetProcess();

	UFUNCTION(BlueprintCallable)
	void ExecuteSkill();

	UFUNCTION(BlueprintCallable)
	int32 GetHealth();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	int32 GetMoney();
};
