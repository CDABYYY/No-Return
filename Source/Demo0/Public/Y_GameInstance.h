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

	virtual void Shutdown()override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UY_RoomWidget* CurrentRoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AY_Character* MainCharacter;

	UFUNCTION(BlueprintImplementableEvent)
	void SetColor(UMeshComponent* MeshComponent, FName MaterialName);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowNiagara(FName NiagaraName, FVector Position, FRotator Direction, float Duration, float Velocity);

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

	//Debug, 1: Card, 2:Room, 3:Equipment, 4:Enemy, 5:Buff
	UFUNCTION(BlueprintCallable)
	void DebugSettings(int32 Type, int32 ID);

	TSharedPtr<class Y_Fighting> FightInfo;

	void AddAtk(class AY_Character* owner);
	void HelpTick(float DeltaTime);
	void DeleteAtk(class AY_Character* owner);

	UFUNCTION(BlueprintCallable)
	void BeginGame();

	//0: Nothing, 1: Fighting, 2:Eventing, 3:Mapping Need Add
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 GameStatus;

	UFUNCTION(BlueprintImplementableEvent)
	AActor* GISpawnActor(int32 SpawnType, FName SpawnClass, FVector SpawnVector, FRotator SpawnRotator);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundCue* MapSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* MapSoundPlaying;

	//Temp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundCue* OpenMapSound;
};
