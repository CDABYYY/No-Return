// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Y_Card.generated.h"


UCLASS()
class DEMO0_API AY_Card : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AY_Card();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UFUNCTION(BlueprintCallable)
	void CardShapeInit(const TCHAR* name);
	
	//Can't Use. Show ConstructorHelpers is not declared.
	/*template<const char* name>
	void CardInitApp();*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Clicked();

	UFUNCTION(BlueprintCallable)
	virtual void Play();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Shape")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 CardCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 NowCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	FText CardDescibe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 CardID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	FText CardLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	UTexture2D* Picture;

	UFUNCTION(BlueprintCallable)
	void Init();

	TSharedPtr<class Y_CardInfo> Info;

	UFUNCTION(BlueprintCallable)
	void SetColor(FName MaterialName);

	UFUNCTION(BlueprintCallable)
	virtual bool AcceptFloor(class AY_Floor* TargetFloor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	float NowPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	float ToPosition;

	static void UseCard(AY_Card* UsedCard);

	static void DrawCard(TSharedPtr<class Y_CardInfo> ToDrawCard, bool VoidSpawn = false);
	
	static void DrawCard(int32 DrawCount = 1);

	//static void DrawCard(FName DrawCardName = FName());

	static TMap<FName, TSubclassOf<AY_Card>>& AddMap(FName AddCardName = FName(), TSubclassOf<AY_Card> AddCardClass = TSubclassOf<AY_Card>());

	static FName CardName;

	static TMap<FName, TSubclassOf<AY_Card>>& CM;
};

