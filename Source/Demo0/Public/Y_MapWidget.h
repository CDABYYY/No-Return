// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Y_MapWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API UY_MapWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> Profileclass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Occupation Ratio"))
	float a = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Deformity Ratio"))
	float b = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Weight of LargeLevel"))
	TMap<int32, float> weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Weight of SmallLevel"))
	TMap<int32, float> slevel;

	float ax = 0, bx = 0;

	TMap<int32, float> Rates = TMap<int32, float>();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Each Levels"))
	TArray<int32> levels = TArray<int32>();

	//Every Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UUserWidget*> plevel;

	//(Floor << 20) + (A << 10) + B
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> pway;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FVector2D> WayToDraw;

	UFUNCTION(BlueprintImplementableEvent)
	UUserWidget* DrawEvent(float RateA,float RateB);

	TArray<int32> GetWay(int32 a0, int32 b0, int32 f0);

	UFUNCTION(BlueprintCallable)
	void GetMap();

	UFUNCTION(BlueprintCallable)
	void DrawWay(FVector2D ParentSize);

	float calculate(int32 a0, int32 f);
};
