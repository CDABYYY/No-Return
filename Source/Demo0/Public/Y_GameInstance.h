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
	TArray<class AY_Character*>Enemys;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Money;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector NowVector;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator NowRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SceneVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SceneScale = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AY_Character* MainCharacter;

	UFUNCTION(BlueprintImplementableEvent)
	void SetColor(UMeshComponent* MeshComponent, FName MaterialName);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FName, TSubclassOf<class AY_Character>> AllyClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, TSubclassOf<class AY_Character>> EnemyClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, TSubclassOf<class AY_Card>> CardClasses;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FName, TSubclassOf<class AY_Floor>> FloorClasses;

	UFUNCTION(BlueprintCallable)
	void EndRoom();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunTime = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TickTime = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	float TopoRate = 1;

	UFUNCTION(BlueprintCallable)
	void ChangeTopoRate(float MultiplyRate);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<class AY_Character*> AtkOrder;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRandomStream RandomStream;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HaveRandoms;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	static TMap<FString, UTexture2D*> Pictures;

	UFUNCTION(BlueprintCallable)
	UTexture2D* LoadPicture(const FString& FilePath);

	TSharedPtr<class Y_Fighting> FightInfo;

	void AddAtk(class AY_Character* owner);
	void HelpTick(float DeltaTime);
	void DeleteAtk(class AY_Character* owner);
	//void UpdateOrder();
	//Sort is Failed. I just can't understand.
};
