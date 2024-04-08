// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Y_Floor.generated.h"

UCLASS()
class DEMO0_API AY_Floor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AY_Floor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 SerialNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	class AY_Character* StandCharacter;

	UFUNCTION(BlueprintCallable)
	virtual void Clicked();

	UFUNCTION(BlueprintCallable, Category = "Calculate")
	FVector TargetLocation();

	UFUNCTION(BlueprintCallable)
	void SetColor(FName MaterialName);

	TSharedPtr<class Y_FloorInfo> Info;
};

class DEMO0_API Y_FloorInfo {
public:
	class AY_Floor* Owner;
};