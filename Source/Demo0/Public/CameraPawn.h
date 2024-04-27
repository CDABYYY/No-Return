// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CameraPawn.generated.h"

UCLASS()
class DEMO0_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySceneComponent")
	USpringArmComponent* MySpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySceneComponent")
	UCameraComponent* MyCamera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "MySceneComponent")
	UStaticMeshComponent* MyStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySceneComponent")
	UStaticMeshComponent* CardSpawnStart;

	//void Move(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyValue")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyValue")
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyValue")
	bool ClickAble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyValue")
	bool FindingObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choosing")
	class AY_Card* ChoosedCard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choosing")
	class AY_Floor* ChoosedFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choosing")
	class AY_Floor* LookingFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choosing")
	float LookingTime;

	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	void MouseLeftPress();

	UFUNCTION(BlueprintCallable)
	void MouseLeftRelease();
};
