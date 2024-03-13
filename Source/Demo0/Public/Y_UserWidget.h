// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_UserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 CurrentHealth = 100;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MaxHealth = 100;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AY_Character* OwnerCharacter;

	UFUNCTION(BlueprintCallable)
	void UserWidgetInit(class AY_Character* Owner);

	UFUNCTION(BlueprintCallable)
	float GetHealthPersent();
};
