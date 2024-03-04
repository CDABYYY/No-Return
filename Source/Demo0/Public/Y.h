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

	static float getRandom();

	template<typename ...Argv>
	static void Log(bool test, const TCHAR Format[], Argv... Params) {
		FString s = FString::Printf(Format, Params...);
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, s);
		//UE_LOG(LogTemp, Warning, Format, Params...);
	}

	template<typename ...Argv>
	static void Log(const TCHAR Format[], Argv... Params) {
		FString s = FString::Printf(Format, Params...);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, s);
		//UE_LOG(LogTemp, Warning, Format, Params...);
	}

	template<typename T>
	static T getRandom(TMap<T, float> m) {
		float tot = 0;
		for (auto&& p : m)tot += p.Value;
		float choosed = getRandom() * tot;
		for (auto&& p : m) {
			if (choosed < p.Value)return p.Key;
			choosed -= p.Value;
		}
		return m.begin()->Key;
	}
};
