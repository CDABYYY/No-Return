// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_EquipmentW.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_EquipmentW : public UUserWidget
{
	GENERATED_BODY()
public:
	TSharedPtr<class Y_Equipment> Info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UY_EquipmentH* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EquipmentID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EquipmentCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EquipmentCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Picture;

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void Update();

	UFUNCTION(BlueprintCallable)
	void Enter();

	UFUNCTION(BlueprintCallable)
	void Leave();

	UFUNCTION(BlueprintCallable)
	void Press();

	UFUNCTION(BlueprintCallable)
	void HelpTick(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void SetPos(float Pos);
};
