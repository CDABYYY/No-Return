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
	static class UY_GameInstance*& GetGameInstance();

	static class ACameraPawn*& GetPlayer();

	static class AY_Character*& GetMainCharacter();

	static class AY_PlayerController*& GetController();

	static class Y_Fighting* GetGameInfo();

	static class AY_Floor*& GetChoosedFloor();

	static class AY_Card*& GetChoosedCard();

	static TArray<class AY_Card*>& GetCards();

	static TArray<class AY_Floor*>& GetFloors();

	static TArray<class AY_Character*>& GetEnemys();

	static bool& IsPressingCard();

	static TSharedPtr<class Y_CardInfo> GetChoosingCard();

	static float& GetRunTime();

	static TSharedPtr<class Y_Equipment> GetChoosingEquipment();

	static bool& IsPressingEquipment();

	static FVector& GetLocation();

	static FRotator& GetRotation();

	static int32 ExecutePureAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, FString TriggerAction, bool TryAttack = false);

	static int32 ExecuteAction(class AY_Character* FromCharacter, class AY_Character* ToCharacter, class Y_StatusBar& ToBuffs, FString TriggerAction, bool TryAttack = false);

	static float getRandom();

	static class UWorld* GetWorld();

	static UTexture2D* LoadPicture(const FString& FilePath);

	static int32& GetCurrentLevel();

	static const TCHAR* toS(FText ReadyText);

	template <typename T>
	static TArray<T> GetRandomArray(TArray<T> TargetArray, int32 Counts = 3) {
		TArray<T> Answer;
		for (int32 i = 0; i < TargetArray.Num(); i++) {
			if (Counts - Answer.Num() >= TargetArray.Num() - i || getRandom() < (float)Counts / TargetArray.Num()) {
				Answer.Add(TargetArray[i]);
				if (Answer.Num() >= Counts)break;
			}
		}
		return Answer;
	}

	template<typename FType,typename ...Argv>
	static void Log(int32 TestColor, const FType& Format, Argv... Params) {
		FString s = FString::Printf(Format, Params...);
		if(TestColor == 0)
		{
			if(IsValid(GEngine))
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, s);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
		}
		else {
			if(IsValid(GEngine))
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, s);
				UE_LOG(LogTemp, Error, TEXT("%s"), *s);
		}

		//::ELogVerbosity::
	}

	template<typename FType,typename ...Argv>
	static void Log(const FType& Format, Argv... Params) {
		FString s = FString::Printf(Format, Params...);
		//GetGameInstance()->GetEngine()->AddOnScreenDebugMessage(-1, 5, FColor::Blue, s);
		UE_LOG(LogTemp, Log, TEXT("%s"), *s);
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
	
	template <typename FType,typename...Argv>
	static FText PrintText(const FType& type, Argv... argv) {
		return FText::FromString(FString::Printf(type, argv...));
	}

	template <typename T,typename...Argv>
	static TSharedPtr<T> YMakeShared(Argv...argv) {
		TSharedPtr<T> TmpP = MakeShared<T>();
		TmpP->Init(argv...);
		return TmpP;
	}

	template<typename T>
	static TSharedPtr<T> YMakeShared() {
		return MakeShared<T>();
	}

	template<class T1>
	class Y_SubClassIF {
	public:
		template<class...Argv>
		TSharedPtr<T1> NewObject(Argv...argv) {
			TSharedPtr<T1> TmpP = NewObject();
			TmpP->Init(argv...);
			return TmpP;
		}
		template<>
		TSharedPtr<T1> NewObject() { return NewObject(); }

		virtual TSharedPtr<T1> NewObject() = 0;
		virtual ~Y_SubClassIF() {};
	};


	template<class T2, class T3>
	class Y_SubClassIM :public Y_SubClassIF<T2> {
	public:
		TSharedPtr<T2> NewObject()override {
			return MakeShared<T3>();
		}
	};

	
	template<class T1,class T2>
	static TSharedPtr<Y_SubClassIF<T1>> StoreClass() {
		return MakeShared<Y_SubClassIM<T1, T2>>();
	}

	static TMap<int32, TSharedPtr<Y_SubClassIF<class Y_CardInfo>>> CardClass;
	template<class T>
	static void LoadCard(int32 ID) {
		CardClass.Add(ID, StoreClass<Y_CardInfo, T>());
	}

	static TMap<int32, TSharedPtr<Y_SubClassIF<class Y_EnemyInfo>>> CharacterClass;
	template<class T>
	static void LoadCharacter(int32 ID) {
		CharacterClass.Add(ID, StoreClass<Y_EnemyInfo, T>());
	}

	static TMap<int32, TSharedPtr<Y_SubClassIF<class Y_FloorInfo>>> FloorClass;
	template<class T>
	static void LoadFloor(int32 ID) {
		FloorClass.Add(ID, StoreClass<Y_FloorInfo, T>());
	}

	static TMap<int32, TSharedPtr<Y_SubClassIF<class Y_Buff>>> BuffClass;
	template<class T>
	static void LoadBuff(int32 ID) {
		BuffClass.Add(ID, StoreClass<Y_Buff, T>());
	}

	static TMap<int32, TSharedPtr<Y_SubClassIF<class Y_RoomInfo>>> RoomClass;
	template<class T>
	static void LoadRoom(int32 ID) {
		RoomClass.Add(ID, StoreClass<Y_RoomInfo, T>());
	}

	static TMap<int32, TSharedPtr<Y_SubClassIF<class Y_Equipment>>> EquipmentClass;
	template<class T>
	static void LoadEquipment(int32 ID) {
		EquipmentClass.Add(ID, StoreClass<Y_Equipment, T>());
	}

	template<typename T>
	static TSharedPtr<T> getRandom(TArray<TSharedPtr<T>>& randomArray) {
		float tot = 0;
		TArray<float> pWeights;
		for (auto&& p : randomArray)
		{
			int TW = p->GetWeight();
			tot += TW;
			pWeights.Add(TW);
		}
		float choosed = getRandom() * tot;
		for (int i = 0; i < randomArray.Num();i++) {
			if (choosed < pWeights[i]) return randomArray[i];
			choosed -= pWeights[i];
		}
		return randomArray[0];
	}
};

