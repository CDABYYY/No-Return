// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_CardW.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_CardW : public UUserWidget
{
	GENERATED_BODY()
public:
	TSharedPtr<class Y_CardInfo> CardInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NowXPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NowYPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NowAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToXPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToYPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LivingTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UY_CardH* Owner;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CardID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Picture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CardDescribe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CardName;

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

	UFUNCTION(BlueprintCallable)
	void ArrangePos(float XPos, float YPos, float Angle, float Time);

	UFUNCTION(BlueprintImplementableEvent)
	void SetPos(float XPos, float YPos, float Angle);
};
