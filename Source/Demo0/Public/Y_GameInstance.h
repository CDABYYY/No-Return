// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	static UY_GameInstance* YGI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ACameraPawn* YC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class AY_Card*> Cards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class AY_Floor*>Floors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AY_Character* MainCharacter;

	UFUNCTION(BlueprintImplementableEvent)
	void SetColor(UMeshComponent* MeshComponent, FName MaterialName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunTime = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<class AY_Character*> AtkOrder;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRandomStream RandomStream;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HaveRandoms;

	void AddAtk(class AY_Character* owner);
	void HelpTick(float DeltaTime);
	void DeleteAtk(class AY_Character* owner);
	//void UpdateOrder();
	//Sort is Failed. I just can't understand.
};
