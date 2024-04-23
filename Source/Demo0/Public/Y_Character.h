// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Y_Character.generated.h"

UCLASS()
class DEMO0_API AY_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AY_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	class AY_Floor* StandFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 CharacterStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 CharacterPriority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 CharacterAttackTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 CharacterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	int32 Facing = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	float Rotating = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	float ActionRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YValue")
	class UY_BuffBar* BuffBar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UWidgetComponent* MyWidgetHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* BuffWidget;

	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class Y_StatusBar* Buffs;

	class Y_StatusBar* ShowBuffs;

	virtual void AddBuff(TSharedPtr<class Y_Buff> Buff, bool Execute);

	virtual bool ChangeFacing(int32 ToChange);

	//UFUNCTION(BlueprintCallable)
	virtual int32 ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, int32 ExecuteCondition,FString TriggerAction, bool TryAttack = false);

	UFUNCTION(BlueprintCallable)
	void CharacterMove(int32 Distance, bool Execute, FText Causer);

	UFUNCTION(BlueprintCallable)
	virtual void Update();

	UFUNCTION(BlueprintCallable)
	virtual void Attack();

	UFUNCTION(BlueprintCallable)
	virtual void CharacterDead();

	UFUNCTION(BlueprintCallable)
	virtual void CharacterLogicalMove(class AY_Floor* TargetFloor);

	//UFUNCTION(BlueprintCallable)
	virtual void AddBuffImmediately(TSharedPtr<class Y_Buff> AddedBuff);

	UFUNCTION(BlueprintCallable)
	virtual void ChangeAttackTime(int32 ChangedTime);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MyPlayMontage(FName PlayName, class AY_Floor* ToFloor, float PlayRate, bool Offset);

	TSharedPtr<class Y_EnemyInfo> Info;

};
