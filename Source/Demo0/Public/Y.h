// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DEMO0_API Y
{
public:
	Y();
	~Y();
	static class UY_GameInstance* GetGameInstance();

	static class ACameraPawn* GetPlayer();

	static TArray<class AY_Card*>& GetCards();

	static TArray<class AY_Floor*>& GetFloors();

	static class AY_Character* GetMainCharacter();
};
