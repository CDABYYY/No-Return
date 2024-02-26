// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Y_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API AY_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HUDAsset;

	UUserWidget* MyHUD;
protected:
	virtual void BeginPlay() override;
};
