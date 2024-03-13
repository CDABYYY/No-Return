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
	static AY_PlayerController* ThisPlayerController;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HUDAsset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* MyY_HUD;
protected:
	virtual void BeginPlay() override;
};
