// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Y_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO0_API AY_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	static AY_PlayerController* ThisPlayerController;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HUDAsset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* MyY_HUD;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UY_HUD* PCHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UY_MapWidget* MapWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MapAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UY_EventWidget* EventWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> EventAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UY_CardH* CardWidget;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowCards(bool Reversed);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowMap();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseMap();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMap();

	UFUNCTION(BlueprintImplementableEvent)
	void LoadMap();

	UFUNCTION(BlueprintImplementableEvent)
	void EndRoom();

	UFUNCTION(BlueprintImplementableEvent)
	void LoadHUD();

	void BeginEvent(TSharedPtr<class Y_EventInfo> EventInfo);

protected:
	virtual void BeginPlay() override;
};
