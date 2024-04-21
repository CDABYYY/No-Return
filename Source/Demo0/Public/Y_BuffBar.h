// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_BuffBar.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_BuffBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AY_Character* Owner;

	UFUNCTION(BlueprintCallable)
	void Update();

	UFUNCTION(BlueprintImplementableEvent)
	class UY_BuffIcon* NewBuffIcon();
};
