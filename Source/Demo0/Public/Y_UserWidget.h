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
	float CurrentHealth = 100;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth = 100;
};
