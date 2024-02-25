// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CameraPawn.h"
#include "Y_Card.h"
#include "Y_Floor.h"
#include "Y_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UY_GameInstance();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	static ACameraPawn* YC;

	static TArray<AY_Card*> Cards;

	static TArray<AY_Floor*>Floors;

	static class AY_Character* MainCharacter;

	UFUNCTION(BlueprintImplementableEvent)
	void SetColor(UMeshComponent* MeshComponent, FName MaterialName);
};
